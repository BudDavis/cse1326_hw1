#include <stdio.h>
#include <stdlib.h>

#include "icao.hpp"

// All records are in memory in a null terminated list
// of pointers. Think 'C string' but with records
icao_record **list;

// Number of items in the list
unsigned int num_records;

int
main (int argc, char *argv[])
{
  char *file_name = (char *)"iata-icao.csv";
  printf ("This site or product includes "
          "IATA/ICAO List data available from http://www.ip2location.com.\n");
  // find how many we care about
  num_records = num_records_in_file (file_name);
  printf ("%d entries in the list\n", num_records);

  // Allocate storage for the list (include a null at the end)
  list = (icao_record **)calloc (sizeof (icao_record *), num_records + 1);

  // make all the pointers null
  for (unsigned int i = 0; i < (num_records + 1); i++)
    {
      list[i] = (icao_record *)NULL;
    }

  // read the data into the list
  read_data_file (list, num_records, file_name);

  // deal with the user
  int done = 2;
  while (done == 2)
    {
      float lat;
      float lon;
      done = scanf ("%f %f", &lat, &lon);
      if (done == 2)
        {
          print_out_airports (list, lat, lon);
        }
    }

  // clean up
  clean_up (list);
  free (list);

  return 0;
}
