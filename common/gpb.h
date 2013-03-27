#ifndef GPKG_GPB_H
#define GPKG_GPB_H

#include <stdint.h>
#include "binstream.h"
#include "geomio.h"

typedef struct {
    uint8_t version;
    uint32_t srid;
    int has_env_x;
    double min_x;
    double max_x;
    int has_env_y;
    double min_y;
    double max_y;
    int has_env_z;
    double min_z;
    double max_z;
    int has_env_m;
    double min_m;
    double max_m;
} gpb_t;

typedef struct {
    geom_reader_t geom_reader;
    binstream_t stream;
    gpb_t gpb;
    size_t start[GEOM_MAX_DEPTH];
    size_t children[GEOM_MAX_DEPTH];
    int offset;
} gpb_writer_t;

int gpb_writer_init( gpb_writer_t *writer, uint32_t srid );

void gpb_writer_destroy( gpb_writer_t *writer );

uint8_t* gpb_writer_getgpb( gpb_writer_t *writer );

size_t gpb_writer_length( gpb_writer_t *writer );

int gpb_envelope_init_from_wkb(binstream_t *stream, gpb_t *gpb);

size_t gpb_size(gpb_t *gpb);

int gpb_read_header(binstream_t *stream, gpb_t *gpb);

int gpb_write_header(binstream_t *stream, gpb_t *gpb);

#endif
