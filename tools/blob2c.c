//***************************************************************************
// blob2c
// Quick tool to convert a blob into C source code.
// Feel free to use in whatever way you want.
//***************************************************************************

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
   // Check arguments
   if (argc != 4) {
      fprintf(stderr, "Usage: %s <input.blob> <output.c> <array_name>\n", argv[0]);
      return EXIT_FAILURE;
   }
   
   const char *in_name = argv[1];
   const char *out_name = argv[2];
   const char *arary_name = argv[3];
   
   // Open files
   FILE *in = fopen(in_name, "rb");
   FILE *out = fopen(out_name, "w");
   
   if (in == NULL) {
      fprintf(stderr, "Error: can't open input blob \"%s\"\n", in_name);
      return EXIT_FAILURE;
   }
   if (out == NULL) {
      fprintf(stderr, "Error: can't make output file \"%s\"\n", out_name);
      return EXIT_FAILURE;
   }
   
   // Write start of array
   fprintf(out, "static const unsigned char %s[] = {", arary_name);
   
   // Convert the blob into C source code
   // The counter is for the sake of knowing where to do line breaks
   const unsigned BYTES_PER_LINE = 16;
   for (unsigned i = 0; ; i++) {
      // Read from blob
      int byte = fgetc(in);
      if (byte == EOF) break;
      
      // Write byte to C array
      if (i % BYTES_PER_LINE == 0) fputs("\n   ", out);
      fprintf(out, "%3u,", byte);
   }
   
   // Write end of array
   fputs("\n};\n", out);
   
   // Make sure to report any issues
   if (ferror(in)) {
      fprintf(stderr, "Error: problem reading from \"%s\"\n", in_name);
      return EXIT_FAILURE;
   }
   if (ferror(out)) {
      fprintf(stderr, "Error: problem writing into \"%s\"\n", out_name);
      return EXIT_FAILURE;
   }
   
   // Done
   fclose(in);
   fclose(out);
   return EXIT_SUCCESS;
}
