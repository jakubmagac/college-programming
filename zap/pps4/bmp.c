#include "bmp.h"
#include <stdlib.h>


struct bmp_header* read_bmp_header(FILE* stream)
{
  if(!stream) return NULL;
  struct bmp_header* head = malloc(sizeof(*head)+1); 
  
  fseek(stream, 0, SEEK_SET);
  fread(&head->type, 2, 1, stream);
  if(head->type != 19778){
    free(head);
    return NULL;
  } 

  fread(&head->size, 4, 1, stream);
  fread(&head->reserved1, 2, 1, stream);
  fread(&head->reserved2, 2, 1, stream);
  fread(&head->offset, 4, 1, stream);
  fread(&head->dib_size, 4, 1, stream);
  fread(&head->width, 4, 1, stream);
  fread(&head->height, 4, 1, stream);
  fread(&head->planes, 2, 1, stream);
  fread(&head->bpp, 2, 1, stream);
  fread(&head->compression, 4, 1, stream);
  fread(&head->image_size, 4, 1, stream);
  fread(&head->x_ppm, 4, 1, stream);
  fread(&head->y_ppm, 4, 1, stream);
  fread(&head->num_colors, 4, 1, stream);
  fread(&head->important_colors, 4, 1, stream);
  return head;

}

struct pixel* read_data(FILE* stream, const struct bmp_header* header)
{
  if(!stream || !header) return NULL;

  fseek(stream, header->offset, SEEK_SET);
  struct pixel* pixels = malloc(sizeof(*pixels)*(header->width*header->height)); 
  
  int k = 0;
  int dump;

  for(int i=0;i<header->height;i++){
    for(int j=0;j<header->width;j++){
      fread(&pixels[k].blue, 1, 1, stream);
      fread(&pixels[k].green, 1, 1, stream);
      fread(&pixels[k].red, 1, 1, stream);
      k++;
    }

    // ignore padding
    if((header->width % 4) != 0){
      for(int j=0;j<header->width;j++){
        fread(&dump, 1, 1, stream);
      }
    }
  }
  return pixels;
}

struct bmp_image* read_bmp(FILE* stream)
{
  if(!stream) return NULL;

  struct bmp_header* header = read_bmp_header(stream);
  if(header == NULL){
    free(header);
    fprintf(stderr,"Error: This is not a BMP file.\n");
    return NULL;
  } 

  struct pixel* data = read_data(stream, header);   
  if(data == NULL){
    free(header);
    free(data);
    fprintf(stderr,"Error: Corrupted BMP file.\n");
    return NULL;
  } 

  struct bmp_image* img = malloc(sizeof(header) + sizeof(data));
  
  img->data = data;
  img->header = header;
  return img;
}

bool write_bmp(FILE* stream, const struct bmp_image* image)
{
  if(stream == NULL || image == NULL) return false;

  fseek(stream, 0, SEEK_SET);
  fwrite(&image->header->type, 2, 1, stream);
  fwrite(&image->header->size, 4, 1, stream);
  fwrite(&image->header->reserved1, 2, 1, stream);
  fwrite(&image->header->reserved2, 2, 1, stream);
  fwrite(&image->header->offset, 4, 1, stream);
  fwrite(&image->header->dib_size, 4, 1, stream);
  fwrite(&image->header->width, 4, 1, stream);
  fwrite(&image->header->height, 4, 1, stream);
  fwrite(&image->header->planes, 2, 1, stream);
  fwrite(&image->header->bpp, 2, 1, stream);
  fwrite(&image->header->compression, 4, 1, stream);
  fwrite(&image->header->image_size, 4, 1, stream);
  fwrite(&image->header->x_ppm, 4, 1, stream);
  fwrite(&image->header->y_ppm, 4, 1, stream);
  fwrite(&image->header->num_colors, 4, 1, stream);
  fwrite(&image->header->important_colors, 4, 1, stream);

  fseek(stream, image->header->offset, SEEK_SET);
  int k = 0;

  for(int i=0;i<image->header->height;i++){
    for(int j=0;j<image->header->width;j++){
      fwrite(&image->data[k].blue, 1, 1, stream);
      fwrite(&image->data[k].green, 1, 1, stream);
      fwrite(&image->data[k].red, 1, 1, stream);
      k++;
    }

    // add padding
    if((image->header->width % 4) != 0){
      for(int j=0;j<image->header->width;j++){
        fwrite("\0", 1, 1, stream);
      }
    }
  }

  return true;
}

void free_bmp_image(struct bmp_image* image)
{
  if(image != NULL){
    if(image->header != NULL) free(image->header);
    if(image->data   != NULL) free(image->data);
    free(image);
  }
}
