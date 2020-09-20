#include "bmp.h"
#include "transformations.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if(argv[1] == NULL) return 0;
  FILE* stream=fopen(argv[1], "rb+");
  
  struct bmp_header *head = read_bmp_header(stream);
  if(head != NULL) printf("%x\n", head->type);

  struct pixel* pixels = read_data(stream, head);
  if(pixels != NULL) printf("%d\n", pixels[0].green);

  struct bmp_image* img = read_bmp(stream);
  
  if(img != NULL){
    // printf("%d", write_bmp(stream, img));
    // img = rotate_left(img);
    // img = rotate_right(img);
    img = extract(img, "g");
    img = flip_horizontally(img);
    // img = flip_vertically(img);
    // img = crop(img, 50, 50, 150, 150);
    write_bmp(stream, img);
    free_bmp_image(img);
  }

  free(pixels); free(head);
  if(stream != NULL) fclose(stream);

  return 0;
}