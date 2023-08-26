//***************************************************************************
// blob2asm68k
// Quick tool to convert a blob into a 68000 asm file.
// Feel free to use in whatever way you want.
//***************************************************************************

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
   // Check arguments
   if (argc != 5) {
      fprintf(stderr, "Usage: %s <input.blob> <output.68k> "
                      "<label_data> <label_size>\n", argv[0]);
      return EXIT_FAILURE;
   }
   
   const char *in_name = argv[1];
   const char *out_name = argv[2];
   const char *label_data = argv[3];
   const char *label_size = argv[4];
   
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
   
   // Write label to output file
   fprintf(out, "%s:", label_data);
   
   // Convert the blob into 68000 asm
   // The counter is for the sake of knowing where to do line breaks
   const unsigned BYTES_PER_LINE = 16;
   for (unsigned i = 0; ; i++) {
      // Read from blob
      int byte = fgetc(in);
      if (byte == EOF) break;
      
      // Write byte to asm file
      if (i % BYTES_PER_LINE == 0) fputs("\n    dc.b    ", out);
      if (i % BYTES_PER_LINE != 0) fputc(',', out);
      fprintf(out, "$%02X", byte);
   }
   
   // Write equ that calculates the blob size
   fprintf(out, "\n%s equ *-%s\n    even\n", label_size, label_data);
   
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
