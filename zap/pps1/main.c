#include "bmp.h"
#include "playfair.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  unsigned char* encrypted;

  char* reversed = reverse("Hello world!");
  printf("%s\n", reversed);
  free(reversed);

  encrypted = bit_encrypt("Hello world!");
  for(int i=0; i < 12;i++) {
      printf("%x ", encrypted[i]);
  }

  char* decrypted = bit_decrypt(encrypted);
  printf("%s", decrypted);
  free(decrypted);  
  free(encrypted);

  char* encr;
  encr = vigenere_encrypt("ditty", "On posibal zvery a striga zisla dolu odbehla na stranu a cosikamsi doniesla na drevci zopchnutu zabu a pocala ju obracat nad ohnom");
  printf("%s", encr);
  free(encr);

  decrypted = vigenere_decrypt("silkier", "VQGOZXVV");
  printf("%s\n", decrypted);
  free(decrypted);
  encr = playfair_encrypt("SeCReT", "Hello world");
  printf("%s", encr);
  decrypted = playfair_decrypt("SeCReT", encr);
  printf("%s", decrypted);
  free(encr);
  free(decrypted);
  
  encrypted = bmp_encrypt("CoMPuTeR", "Hello world!");
  for(int i=0;i<12;i++){
    printf("%x ", encrypted[i]);
  }
  free(encrypted);


  char* dec = bmp_decrypt("CoMPuTeR", bmp_encrypt("CoMPuTeR", "Hello world!"));
  for(int i=0; i < 12;i++) {
      printf("%c ", dec[i]);
  }
  free(dec);
  return 0;
}
