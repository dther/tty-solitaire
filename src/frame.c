#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include "frame.h"
#include "common.h"

void allocate_frame(struct frame **frame) {
  if (!(*frame = malloc(sizeof(**frame)))) {
    fprintf(stderr, tty_solitaire_error_message(errno, __FILE__, __LINE__));
    exit(errno);
  }
  (*frame)->window = newwin(FRAME_HEIGHT, FRAME_WIDTH, 0, 0);
}

void initialize_frame(struct frame *frame) {
  frame->begin_y = 0;
  frame->begin_x = 0;
}

struct frame *duplicate_frame(struct frame *frame) {
  struct frame *new_frame;

  allocate_frame(&new_frame);
  set_frame(new_frame, frame->begin_y, frame->begin_x);

  return(new_frame);
}

void free_frame(struct frame *frame) {
  if (frame) {
    delwin(frame->window);
  }
  free(frame);
}

void set_frame(struct frame *frame, int begin_y, int begin_x) {
  frame->begin_y = begin_y;
  frame->begin_x = begin_x;
  mvwin(frame->window, begin_y, begin_x);
}