#include "transformations.h"
#include <stdlib.h>
#include <string.h>

struct bmp_image* flip_horizontally(const struct bmp_image* image)
{
  if(image == NULL) return NULL;

  struct bmp_image* flipped_image = (struct bmp_image*)malloc(sizeof(image->header)+sizeof(image->data)); 

  flipped_image->header=(struct bmp_header*)malloc(sizeof(struct bmp_header));
  flipped_image->data=(struct pixel*)malloc(image->header->height*image->header->width * sizeof(struct pixel));
  memcpy(flipped_image->header, image->header, sizeof(struct bmp_header));
  struct pixel data[image->header->height][image->header->width];  
  memcpy(flipped_image->data, image->data, 3*flipped_image->header->width*flipped_image->header->height);

  int k = 0;  
  for(int i=0;i<image->header->height;i++){
    for(int j=0;j<image->header->width;j++){
      data[i][j].blue = image->data[k].blue;  
      data[i][j].green = image->data[k].green; 
      data[i][j].red = image->data[k].red;   
      k++;
    }
  }

  k = 0;
  for(int i=0;i<image->header->height;i++){
    for(int j=image->header->width-1;j>=0;j--){
      flipped_image->data[k].blue = data[i][j].blue;
      flipped_image->data[k].green = data[i][j].green;
      flipped_image->data[k].red = data[i][j].red;
      k++;
    }
  }
  return flipped_image;
}

struct bmp_image* flip_vertically(const struct bmp_image* image)
{
  if(image == NULL) return NULL;

  struct bmp_image* flipped_image = (struct bmp_image*)malloc(sizeof(image->header)+sizeof(image->data)); 

  flipped_image->header=(struct bmp_header*)malloc(sizeof(struct bmp_header));
  flipped_image->data=(struct pixel*)malloc(image->header->height*image->header->width * sizeof(struct pixel));
  memcpy(flipped_image->header, image->header, sizeof(struct bmp_header));
  struct pixel data[image->header->height][image->header->width];  
  memcpy(flipped_image->data, image->data, 3*flipped_image->header->width*flipped_image->header->height);

 
  int k = 0;  
  for(int i=0;i<image->header->height;i++){
    for(int j=0;j<image->header->width;j++){
      data[i][j].blue = image->data[k].blue;  
      data[i][j].green = image->data[k].green; 
      data[i][j].red = image->data[k].red;   
      k++;
    }
  }

  k = 0;
  for(int i=image->header->height-1;i>=0;i--){
    for(int j=0;j<image->header->width;j++){
      flipped_image->data[k].blue = data[i][j].blue;
      flipped_image->data[k].green = data[i][j].green;
      flipped_image->data[k].red = data[i][j].red;
      k++;
    }
  }

  return flipped_image;
}

struct bmp_image* rotate_right(const struct bmp_image* image)
{
  if(image == NULL) return NULL;
  struct bmp_image* flipped_image = (struct bmp_image*)malloc(sizeof(image->header)+sizeof(image->data)); 

  flipped_image->header=(struct bmp_header*)malloc(sizeof(struct bmp_header));
  flipped_image->data=(struct pixel*)malloc(image->header->height*image->header->width * sizeof(struct pixel));
  memcpy(flipped_image->header, image->header, sizeof(struct bmp_header));
  
  flipped_image->header->width = image->header->height;
  flipped_image->header->height = image->header->width;

  struct pixel data[image->header->height][image->header->width];
  memcpy(flipped_image->data, image->data, 3*flipped_image->header->width*flipped_image->header->height);

  int k = 0;  
  for(int i=0;i<image->header->height;i++){
    for(int j=0;j<image->header->width;j++){
      data[i][j].blue = image->data[k].blue;  
      data[i][j].green = image->data[k].green; 
      data[i][j].red = image->data[k].red;   
      k++;
    }
  }

  k = 0;
  for(int i=flipped_image->header->height-1;i>=0;i--){
    for(int j=0;j<flipped_image->header->width;j++){
      flipped_image->data[k].blue = data[j][i].blue;
      flipped_image->data[k].green = data[j][i].green;
      flipped_image->data[k].red = data[j][i].red;
      k++;
    }
  }

  int padding = 0; int size;

  if((flipped_image->header->width % 4) != 0) padding = flipped_image->header->width;
  padding *= flipped_image->header->height;
  size = sizeof(struct bmp_header) + padding + (k*3);
  flipped_image->header->size = size;
  flipped_image->header->image_size = size - 54;

  return flipped_image;

}

struct bmp_image* rotate_left(const struct bmp_image* image)
{ 
  if(image == NULL) return NULL;
  struct bmp_image* flipped_image = (struct bmp_image*)malloc(sizeof(image->header)+sizeof(image->data)); 

  flipped_image->header=(struct bmp_header*)malloc(sizeof(struct bmp_header));
  flipped_image->data=(struct pixel*)malloc(image->header->height*image->header->width * sizeof(struct pixel));
  memcpy(flipped_image->header, image->header, sizeof(struct bmp_header));
  
  flipped_image->header->width = image->header->height;
  flipped_image->header->height = image->header->width;

  struct pixel data[image->header->height][image->header->width];
  memcpy(flipped_image->data, image->data, 3*flipped_image->header->width*flipped_image->header->height);

  int k = 0;  
  for(int i=0;i<image->header->height;i++){
    for(int j=0;j<image->header->width;j++){
      data[i][j].blue = image->data[k].blue;  
      data[i][j].green = image->data[k].green; 
      data[i][j].red = image->data[k].red;   
      k++;
    }
  }

  k = 0;
  for(int i=0;i<flipped_image->header->height;i++){
    for(int j=flipped_image->header->width;j>0;j--){
      flipped_image->data[k].blue = data[j-1][i].blue;
      flipped_image->data[k].green = data[j-1][i].green;
      flipped_image->data[k].red = data[j-1][i].red;
      k++;
    }
  }

  int padding = 0; int size;

  if((flipped_image->header->width % 4) != 0) padding = flipped_image->header->width;
  padding *= flipped_image->header->height;
  size = sizeof(struct bmp_header) + padding + (k*3);
  flipped_image->header->size = size;
  flipped_image->header->image_size = size - 54;

  return flipped_image;
}

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep)
{
  if(image == NULL || colors_to_keep == NULL) return NULL;

  for(int i=0;i<strlen(colors_to_keep);i++){
    if(colors_to_keep[i] != 'r' && colors_to_keep[i] != 'g' && colors_to_keep[i] != 'b') return NULL;
  }

  struct bmp_image* extract_image = (struct bmp_image*)malloc(sizeof(image->header)+sizeof(image->data)); 

  extract_image->header=(struct bmp_header*)malloc(sizeof(struct bmp_header));
  extract_image->data=(struct pixel*)malloc(image->header->height*image->header->width * sizeof(struct pixel));
  memcpy(extract_image->header, image->header, sizeof(struct bmp_header));
  memcpy(extract_image->data, image->data, 3*extract_image->header->width*extract_image->header->height);

  int k = 0;  
  for(int i=0;i<image->header->height;i++){
    for(int j=0;j<image->header->width;j++){
      if(strchr(colors_to_keep, 'b') == NULL) extract_image->data[k].blue = 0;  
      if(strchr(colors_to_keep, 'g') == NULL) extract_image->data[k].green = 0;  
      if(strchr(colors_to_keep, 'r') == NULL) extract_image->data[k].red = 0;  
      k++;
    }
  }

  return extract_image;
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width)
{
  if(image == NULL || image->header->height < height || image->header->width < width) return NULL;
  struct bmp_image* flipped_image = (struct bmp_image*)calloc(sizeof(image->header),sizeof(image->data)); 

  flipped_image->header=(struct bmp_header*)malloc(sizeof(struct bmp_header));
  flipped_image->data=(struct pixel*)calloc(image->header->height * image->header->width, sizeof(struct pixel));
  memcpy(flipped_image->header, image->header, sizeof(struct bmp_header));
  struct pixel data[image->header->height][image->header->width];  
 
  int k = 0;  
  for(int i=0;i<image->header->height;i++){
    for(int j=0;j<image->header->width;j++){
      data[i][j] = image->data[k];  
      k++;
    }
  }
  
  k = 0;
  for(int i=(image->header->height - height - start_y)-1;i<(image->header->height - start_y);i++){
    for(int j=start_x+width;j>=start_x;j--){
      flipped_image->data[k] = data[i][j];
      k++;
    }
  }

  flipped_image->header->height = height;
  flipped_image->header->width = width+2;

  int padding = 0; int size;
  if((flipped_image->header->width % 4) != 0) padding = flipped_image->header->width;
  padding *= flipped_image->header->height;
  size = sizeof(struct bmp_header) + padding + (k*3);
  flipped_image->header->size = size;
  flipped_image->header->image_size = size - 54;

  return flipped_image;
}

