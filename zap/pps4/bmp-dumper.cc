/*
 * bmp-dumper.cc
 * Dumps BMP files in more human-readable format
 *
 * 2020 Branislav Beke @ KB/KPI FEI TUKE SVK
 * Licensed under GNU GPLv3
 */
/*
 * Compile with:
 * $ clang++ -std=c++11 bmp-dumper.cc -o bmp-dumper
 * ... or equivalent
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>
#include <array>
#include <vector>
#include <stdexcept>

#ifndef DISABLE_COLORS // By default enable colors -----------------------------
#define FONT_RESET "\033[0m"
#define FONT_BOLD "\033[1m"
#define FONT_UDL "\033[4m"
#define FONT_RED "\033[;31m"

#define FONT_PX_RED "\033[1;31m"
#define FONT_PX_GREEN "\033[1;32m"
#define FONT_PX_BLUE "\033[1;34m"
#define FONT_PX_PAD "\033[0;37m"
#else // Else set all formatters to blank --------------------------------------
#define FONT_RESET ""
#define FONT_BOLD ""
#define FONT_UDL ""
#define FONT_RED ""

#define FONT_PX_RED ""
#define FONT_PX_GREEN ""
#define FONT_PX_BLUE ""
#define FONT_PX_PAD ""
#endif // ----------------------------------------------------------------------

#define yeet throw

auto decodeB64(std::vector<uint8_t> const& cData) -> std::vector<uint8_t>;
auto readData(std::istream& inStream) -> std::vector<uint8_t>;
void printHeader(std::vector<uint8_t> const& cData);
void printColorData(std::vector<uint8_t> const& cData);

auto main(int argc, char** argv) -> int
{
    try {
        size_t const cHeaderSize = 54;

        std::vector<uint8_t> inData;

        // Read from stdin or from file
        if (argc == 2) {
            // Load from file
            std::cout << "Reading from file... " << argv[1] << std::endl;
            std::filebuf fb;
            fb.open(argv[1], std::ios::in | std::ios::binary);
            if (!fb.is_open()) {
                yeet std::runtime_error(std::string("Cannot open input file ") + argv[1]);
            }
            std::istream inFB{&fb};
            inData = readData(inFB);
        }
        else {
            // Load from stdin
            inData = readData(std::cin);
        }

        // Verify input data
        std::cout << "-> Loaded " << inData.size() << " bytes" << std::endl;
        if (inData.size() < 2) {
            yeet std::runtime_error("Insufficient data");
        }

        if (inData[0] == 'B' and inData[1] == 'M') {
            std::cout << "-> Looks like binary..." << std::endl;
        }
        else {
            std::cout << "-> Looks like base64, decoding..." << std::endl;
            inData = decodeB64(inData);
        }

        // Reject non-BMP data
        if (inData[0] != 'B' and inData[1] != 'M') {
            yeet std::runtime_error("Not a BMP file!");
        }

        std::cout << "-> Assume BMP data" << std::endl;

        if (inData.size() < cHeaderSize) {
            yeet std::runtime_error("Insufficient BMP data (header truncated)");
        }

        // Print header data
        std::cout << std::endl;
        printHeader(inData);

        std::cout << std::endl;
        printColorData(inData);
    }
    catch (std::runtime_error& ex) {
        std::cerr << FONT_RED FONT_BOLD "Exception: " FONT_RESET << ex.what() << std::endl;
        return 1;
    }

    std::cout << std::endl << "--> KTHXBYE <--" << std::endl;

    return 0;
} // ===================================================================================================================

void printColorData(std::vector<uint8_t> const& cD)
{
    std::cout << FONT_BOLD FONT_UDL "Image data" FONT_RESET << std::endl;
    if (cD.size() <= 54) { // NOLINT (readability-magic-numbers)
        std::cout << "-- No image data --" << std::endl;
        return;
    }

    size_t const cWO = 0x12;
    size_t const cHO = cWO + 4;
    size_t const cIO = 54;

    // NOLINTNEXTLINE (readability-magic-numbers)
    int32_t height_ = cD[cHO] | cD[cHO + 1] << 8 | cD[cHO + 2] << 16 | cD[cHO + 3] << 24;
    // NOLINTNEXTLINE (readability-magic-numbers)
    auto const cWidth  = static_cast<size_t>(cD[cWO] | cD[cWO + 1] << 8 | cD[cWO + 2] << 16 | cD[cWO + 3] << 24);
    auto const cHeight = static_cast<size_t>(height_ < 0 ? -height_ : height_);
    auto const cPad    = static_cast<size_t>((cWidth * 3) % 4 != 0 ? 4 - ((cWidth * 3) % 4) : 0);

    std::cout << "->> width: " << cWidth << " height: " << cHeight << std::endl
              << "->> image data bytes: " << cD.size() - cIO << std::endl
              << std::endl;

    int32_t const cLimit = 20;
    if (cWidth > cLimit or cHeight > cLimit) {
        std::cout << "-> Not printing due to image size" << std::endl;
        return;
    }

    for (size_t iRow = 0; iRow < cHeight; iRow++) {
        for (size_t iCol = 0; iCol < cWidth; iCol++) {
            size_t cO = cIO + (cWidth * iRow * 3) + (iCol * 3);
            printf(" " FONT_PX_BLUE "%02x" FONT_PX_GREEN "%02x" FONT_PX_RED "%02x", //
                   cD[cO], cD[cO + 1], cD[cO + 2]);
        }

        for (size_t iPad = 0; iPad < cPad; iPad++) {
            printf(FONT_PX_PAD " 00");
        }

        printf(FONT_RESET "\n");
    }

    std::cout << std::endl;
}

void printHeader(std::vector<uint8_t> const& cD)
{
    // Yeah, well, I'm not taking any chances :D a.k.a. try to explain to users how to install a library
    // clang-format off
#define XB "%02x "
#define PD "   "
#define val2_ (cD[o] | cD[o+1] << 8)
#define val4_ (cD[o] | cD[o+1] << 8 | cD[o+2] << 16 | cD[o+3] << 24)
#define print2B() { printf(FONT_PX_PAD "0x" XB FONT_RESET FONT_BOLD XB XB PD PD "%7d  " FONT_RESET, o, cD[o], cD[o+1], val2_); o += 2; } (void)(0)
#define print4B() { printf(FONT_PX_PAD "0x" XB FONT_RESET FONT_BOLD XB XB XB XB "%7d  " FONT_RESET, o, cD[o], cD[o+1], cD[o+2], cD[o+3], val4_); o += 4; }(void)(0)
    // clang-format on

    unsigned int o = 0;
    printf(FONT_BOLD "Ofst B0 B1 B2 B3  IntVal  Description\n\n" FONT_RESET);

    // Magic bytes - 2 bytes
    print2B();
    printf("Magic bytes ('BM' for BMP)\n");

    // File size - 4 bytes
    print4B();
    printf("Full file size\n");

    // Reserved 1 - 2 bytes
    print2B();
    printf("Reserved\n");

    // Reserved 2 - 2 bytes
    print2B();
    printf("Reserved\n");

    // Offset to image data - 4 bytes
    print4B();
    printf("Offset to image data\n");

    std::cout << std::endl;

    // DIB Header size - 4 bytes
    print4B();
    printf("DIB header size (typ: 40b)\n");

    // Width - 4 bytes
    print4B();
    printf("Image width\n");

    // Height - 4 bytes
    print4B();
    printf("Image height\n");

    // Planes - 2 bytes
    print2B();
    printf("Num of planes\n");

    // Bit per pixel - 2 bytes
    print2B();
    printf("Bits per pixel\n");

    // Compression type - 4 bytes
    print4B();
    printf("Compression type\n");

    // Image size - 4 bytes
    print4B();
    printf("Image data size\n");

    // X-axis PPM - 4 bytes
    print4B();
    printf("X-axis PPM\n");

    // Y-axis PPM - 4 bytes
    print4B();
    printf("Y-axis PPM\n");

    // Num of colors - 4 bytes
    print4B();
    printf("Num of defined colors\n");

    // Important colors - 4 bytes
    print4B();
    printf("Important colors\n");

#undef print2B
#undef print4B
#undef val2_
#undef val4_
#undef PD
#undef XB
} // ===================================================================================================================

auto readData(std::istream& inStream) -> std::vector<uint8_t>
{
    std::vector<uint8_t> inChars;
    for (auto ch = static_cast<uint8_t>(inStream.get()); !inStream.eof(); ch = static_cast<uint8_t>(inStream.get())) {
        inChars.push_back(static_cast<uint8_t>(ch));
    }

    if (inChars.size() % 4 == 1) {
        char const cChar = static_cast<char>(*(inChars.end() - 1));
        if (cChar == '\n') {
            std::cout << "->> Stripping newline (typical for base64 input)" << std::endl;
        }
        else {
            std::cout << "->> WARN: Stripping last byte (val: " << std::dec << +cChar << ")" << std::endl;
        }
        inChars.pop_back();
    }
    return inChars;
} // ===================================================================================================================

auto decodeB64(std::vector<uint8_t> const& cData) -> std::vector<uint8_t>
{
    std::vector<uint8_t> returnData;
    std::string          cChars =    // RFC 4648 - The Base 64 Saga
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ" // Part 1 - Big bois
        "abcdefghijklmnopqrstuvwxyz" // Part 2 - The Sidekicks
        "0123456789+/"               // Part 3 - Numbers and sheiit
        "=";                         // Part 4 - Padding

    if (cData.size() % 4 != 0) {
        std::cerr << cData.size() << std::endl;
        yeet std::runtime_error("Invalid base64 input string (invalid length)");
    }

    // Iterate over string
    for (size_t iOff = 0; iOff < cData.size(); iOff += 4) {
        std::array<std::int8_t, 4> chars;

        for (size_t iPos = 0; iPos < 4; iPos++) {
            // Just because I'm lazy doesn't mean I'm stupid :D
            chars[iPos] = static_cast<int8_t>(cChars.find(static_cast<char>(cData[iOff + iPos])));
            if (chars[iPos] == -1) {
                yeet std::runtime_error("Invalid character in string at position " + std::to_string(iOff + iPos) +
                                        " offending char '" + static_cast<char>(cData[iOff + iPos]) + "'");
            }
        }

        // Convert B64 to bytes
        returnData.push_back(static_cast<uint8_t>((chars[0] << 2) | ((chars[1] >> 4) & 3)));
        // NOLINTNEXTLINE (readability-magic-numbers)
        returnData.push_back(static_cast<uint8_t>((chars[1] << 4) | ((chars[2] >> 2) & 15)));
        // NOLINTNEXTLINE (readability-magic-numbers)
        returnData.push_back(static_cast<uint8_t>((chars[2] << 6) | (chars[3] & 63)));
    }

    return returnData;
} // ===================================================================================================================

// vim: fenc=utf-8:ft=cpp:ts=4:sts=4:sw=4
