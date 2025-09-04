#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "icao.h"

unsigned int
num_records_in_file (char *fname)
{
  //  detemine how many records in the file,
  FILE *fd;
  unsigned int num_records = 0;

  fd = fopen (fname, "r");
  while (!feof (fd))
    {
      // each line is less than 255 chars.. by a lot
      char x[255];
      fgets (x, 255, fd);
      num_records++;
    }

  // close it
  fclose (fd);

  // The first record is a 'header', so we don't care about it.
  // Above code will have 1 more than the actual number since the final
  // fgets() triggers the eof, it does not read in data
  return num_records - 2;
}

void
read_data_file (icao_record *list[], unsigned int num_records, char *fname)
{
  // read the data into the list
  FILE *fd;

  fd = fopen (fname, "r");
  int first = 1;
  int i = 0; // using array notation

  while (!feof (fd))
    {
      // each line is less than 255 chars.. by a lot
      char t[256] = { 0 };
      fgets (t, 255, fd);

      // strip out the double quotes
      for (unsigned int i = 0; i < strlen (t); i++)
        {
          if (t[i] == '"')
            {
              unsigned int j;
              for (j = i; j < strlen (t); j++)
                {
                  t[j] = t[j + 1];
                }
              t[j] = 0;
            }
        }

      // now process it
      if (first)
        {
          first = 0;
        }
      else if (feof (fd))
        {
          ;
        }
      else
        {
          list[i] = (icao_record *)malloc (sizeof (icao_record));
          char *p = strtok (t, (const char *)",");
          list[i]->country_code = (char *)malloc (strlen (p) + 1);
          strcpy (list[i]->country_code, p);
          p = strtok (NULL, (const char *)",");
          list[i]->region_name = (char *)malloc (strlen (p) + 1);
          strcpy (list[i]->region_name, p);
          p = strtok (NULL, (const char *)",");
          list[i]->iata = (char *)malloc (strlen (p) + 1);
          strcpy (list[i]->iata, p);
          p = strtok (NULL, (const char *)",");
          list[i]->icao = (char *)malloc (strlen (p) + 1);
          strcpy (list[i]->icao, p);
          p = strtok (NULL, (const char *)",");
          list[i]->airport = (char *)malloc (strlen (p) + 1);
          strcpy (list[i]->airport, p);
          p = strtok (NULL, (const char *)",");
          list[i]->latitude = atof (p);
          p = strtok (NULL, (const char *)",");
          list[i]->longitude = atof (p);
          i++;
        }
    }
  fclose (fd);
}
void
print_out_airports (icao_record **p, float lat, float lon)
{
  int count = 0;
  icao_record **t = p;
  while (*t)
    {
      if (((int)(*t)->latitude == (int)lat)
          && ((int)(*t)->longitude == (int)lon))
        {
          count++;
          printf ("%d) %s %f %f\n", count, (*t)->airport, (*t)->latitude,
                  (*t)->longitude);
        }
      t++;
    }
}

void
clean_up (icao_record **p)
{
  icao_record **t = p;
  while (*t)
    {
      if ((*t)->country_code)
        {
          free ((*t)->country_code);
        }
      if ((*t)->region_name)
        {
          free ((*t)->region_name);
        }
      if ((*t)->iata)
        {
          free ((*t)->iata);
        }
      if ((*t)->icao)
        {
          free ((*t)->icao);
        }
      if ((*t)->airport)
        {
          free ((*t)->airport);
        }
      free (*t);
      t++;
    }
};
