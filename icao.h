#pragma once

struct icao_record
{
  char *country_code;
  char *region_name;
  char *iata;
  char *icao;
  char *airport;
  float latitude;
  float longitude;
};

unsigned int num_records_in_file (char *fname);
void read_data_file (icao_record *list[], unsigned int num_records,
                     char *fname);
void print_out_airports (icao_record **p, float lat, float lon);
void clean_up (icao_record **p);
