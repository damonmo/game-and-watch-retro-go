#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

#include "driver.h"
#include "stack_malloc.h"
#include "rom_manager.h"

/* Verbose outputs to error.log ? */
#define VERBOSE 	0

#if VERBOSE
#define LOG(x)	logerror x
#else
#define LOG(x)	/* x */
#endif

char *roms = NULL;
char **rompathv = NULL;
int rompathc = 0;

char *samples = NULL;
char **samplepathv = NULL;
int samplepathc = 0;

char *cfgdir, *nvdir, *hidir, *inpdir, *stadir;
char *memcarddir, *artworkdir, *screenshotdir;
char *cheatdir;	/* Steph */

char *alternate_name;				   /* for "-romdir" */

typedef enum
{
	kPlainFile,
	kRAMFile,
	kZippedFile
}	eFileType;

typedef struct
{
	FILE *file;
	unsigned char *data;
	unsigned int offset;
	unsigned int length;
	eFileType type;
	unsigned int crc;
}	FakeFileHandle;

static int checksum_file (const char *file, unsigned char **p, unsigned int *size, unsigned int *crc);

void decompose_rom_sample_path (char *rompath, char *samplepath)
{
}

/*
 * file handling routines
 *
 * gamename holds the driver name, filename is only used for ROMs and samples.
 * if 'write' is not 0, the file is opened for write. Otherwise it is opened
 * for read.
 */

int osd_faccess (const char *newfilename, int filetype)
{
	return 0;
}

UINT32 create_path_recursive(char *path)
{
	return (0);
}

void *osd_fopen (const char *game, const char *filename, int filetype, int _write)
{
    char *name;
    char *data;
    unsigned short name_length;
    unsigned int data_length;
    unsigned short num_files;
    char *addr;
	int found = 0;
	
	FakeFileHandle *f = (FakeFileHandle *) stack_malloc(sizeof (FakeFileHandle));

	if( !f )
	{
		logerror("osd_fopen: failed to mallocFakeFileHandle!\n");
        return 0;
	}
	memset (f, 0, sizeof (FakeFileHandle));

	switch( filetype )
    {
        case OSD_FILETYPE_ROM:
            addr = ROM_DATA;
            num_files = *(unsigned short*)addr;
            addr = addr + 2;

            for (int i=0; i<num_files && !found; i++)
            {
                name = addr;
                name_length = strlen(addr);
                addr = addr + name_length + 1;
                data_length = *(unsigned int*)addr;
                addr = addr + 4;
                data = addr;
                if (strcmp(name, filename)==0)
                {
                    f->type = kRAMFile;
                    f->offset = 0;
                    f->data = data;
                    f->length = data_length;
                    f->crc = 0;
                    found = 1;
                }
                addr = addr + data_length;
            }
            break;
      default:
         logerror("osd_fopen(): unknown filetype %02x\n",filetype);
   }
	if( !found )
	{
		stack_free(f);
		return 0;
	}
	return f;
}

int osd_fread (void *file, void *buffer, int length)
{
    FakeFileHandle *f = (FakeFileHandle *) file;
    if( f->data )
    {
        if( length + f->offset > f->length )
            length = f->length - f->offset;
        memcpy(buffer, f->offset + f->data, length);
        f->offset += length;
        return length;
    }
    return 0;
}

int osd_fread_swap (void *file, void *buffer, int length)
{
	int i;
	unsigned char temp;
	int res = osd_fread (file, buffer, length);
	unsigned char *buf = (unsigned char*)buffer;

	for( i = 0; i < length; i += 2 )
	{
		temp = buf[i];
		buf[i] = buf[i + 1];
		buf[i + 1] = temp;
	}

	return res;
}

void* osd_fdata (void *file)
{
    FakeFileHandle *f = (FakeFileHandle *) file;
    return f->data;
}

int osd_fwrite (void *file, const void *buffer, int length)
{
   return 0;
}

int osd_fwrite_swap (void *file, const void *buffer, int length)
{
   return 0;
}

int osd_fread_scatter (void *file, void *buffer, int length, int increment)
{
	unsigned char *buf = (unsigned char*)buffer;
	FakeFileHandle *f = (FakeFileHandle *) file;
	unsigned char tempbuf[4096];
	int totread, r, i;

	switch( f->type )
   {
      case kPlainFile:
      case kZippedFile:
      case kRAMFile:
         /* reading from the RAM image of a file */
         if( f->data )
         {
            if( length + f->offset > f->length )
               length = f->length - f->offset;
            for( i = 0; i < length; i++ )
            {
               *buf = f->data[f->offset + i];
               buf += increment;
            }
            f->offset += length;
            return length;
         }
         break;
   }

	return 0;
}



int osd_fseek (void *file, int offset, int whence)
{
	FakeFileHandle *f = (FakeFileHandle *) file;
	int err = 0;

	switch( f->type )
   {
      case kPlainFile:
      case kZippedFile:
      case kRAMFile:
         /* seeking within the RAM image of a file */
         switch( whence )
         {
            case SEEK_SET:
               f->offset = offset;
               break;
            case SEEK_CUR:
               f->offset += offset;
               break;
            case SEEK_END:
               f->offset = f->length + offset;
               break;
         }
         break;
   }

	return err;
}

void osd_fclose (void *file)
{
   FakeFileHandle *f = (FakeFileHandle *) file;
   stack_free(f);
}

static int checksum_file (const char *file, unsigned char **p, unsigned int *size, unsigned int *crc)
{
   FakeFileHandle *f = (FakeFileHandle *) file;
   *size = f->length;
   *crc = 0;
   return 0;
}

int osd_fchecksum (const char *game, const char *filename, unsigned int *length, unsigned int *sum)
{
	return 0;
}

int osd_fsize (void *file)
{
    FakeFileHandle *f = (FakeFileHandle *) file;
    return f->length;
}

unsigned int osd_fcrc (void *file)
{
	FakeFileHandle *f = (FakeFileHandle *) file;
	return f->crc;
}

int osd_fgetc(void *file)
{
   return EOF;
}

int osd_ungetc(int c, void *file)
{
   return EOF;
}

char *osd_fgets(char *s, int n, void *file)
{
   return NULL;
}

int osd_feof(void *file)
{
   return 1;
}

int osd_ftell(void *file)
{
   return -1L;
}

int osd_display_loading_rom_message (const char *name, int current, int total)
{
	if( name )
		printf ("loading %-12s\n", name);
	else
		printf ("             \n");
	return 0;
}
