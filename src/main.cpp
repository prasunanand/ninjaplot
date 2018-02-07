#include <iostream>
#include <string.h>
#include "agg_rendering_buffer.h"
#include "backends/canvas.h"
#include <stdio.h>

using namespace std;
int main2()
{
  cout << "Hello from Ninjaplot" << endl;
  check();
  return 0;
}


enum
{
  frame_width = 320,
  frame_height = 200
};

// Writing the buffer to a .PPM file, assuming it has 
// RGB-structure, one byte per color component
//--------------------------------------------------
bool write_ppm(const unsigned char* buf, 
             unsigned width, 
             unsigned height, 
             const char* file_name)
{
  FILE* fd = fopen(file_name, "wb");
  if(fd)
  {
    fprintf(fd, "P6 %d %d 255 ", width, height);
    fwrite(buf, 1, width * height * 3, fd);
    fclose(fd);
    return true;
  }
  return false;
}

// Draw a black frame around the rendering buffer, assuming it has 
// RGB-structure, one byte per color component
//--------------------------------------------------
void draw_black_frame(agg::rendering_buffer& rbuf)
{
  unsigned i;
  for(i = 0; i < rbuf.height(); ++i)
  {
    unsigned char* p = rbuf.row_ptr(i);
    *p++ = 0; *p++ = 0; *p++ = 0;
    p += (rbuf.width() - 2) * 3;
    *p++ = 0; *p++ = 0; *p++ = 0;
  }
  memset(rbuf.row_ptr(0), 0, rbuf.width() * 3);
  memset(rbuf.row_ptr(rbuf.height() - 1), 0, rbuf.width() * 3);
}


int main()
{
  // Free memory
  main2();

  unsigned char* buffer = new unsigned char[frame_width * frame_height * 3];

  memset(buffer, 255, frame_width * frame_height * 3);

  agg::rendering_buffer rbuf(buffer, 
                             frame_width, 
                             frame_height, 
                             frame_width * 3);

  unsigned i;
  for(i = 0; i < rbuf.height()/2; ++i)
  {
    unsigned char* ptr = rbuf.row_ptr(i) + i * 3;
    
    *ptr++ = 127; // R
    *ptr++ = 200; // G
    *ptr++ = 98;  // B
  }

  draw_black_frame(rbuf);
  write_ppm(buffer, frame_width, frame_height, "agg_test.ppm");

  delete [] buffer;
  return 0;
}
