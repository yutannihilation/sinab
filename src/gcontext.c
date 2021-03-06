#include "renderer.h"

/* If defined, print out debug messages */
/*#define DEBUG_MSG*/

/* GContext is similar to R_GE_gcontext from R_ext/GraphicsEngine.h */

/* create a new graphics context object */
GContext* gcontext_new() {
#ifdef DEBUG_MSG
  Rprintf("gcontext_new() called.\n");
#endif
  
  GContext* gc = (GContext*) Calloc(1, GContext);

  strcpy(gc->color, "black");
  strcpy(gc->fill, "black");
  strcpy(gc->fontfamily, "");
  gc->fontface = 1;
  gc->fontsize = 12;
  gc->lineheight = 1.2;
  gc->linetype = 1;
  gc->linewidth = 1.;
  return gc;
}

/* create a new graphics context object via copying */
GContext* gcontext_clone(GContext* source) {
#ifdef DEBUG_MSG
  Rprintf("gcontext_clone() called.\n");
#endif
  
  GContext* gc = (GContext*) Calloc(1, GContext);
  
  strcpy(gc->color, source->color);
  strcpy(gc->fill, source->fill);
  strcpy(gc->fontfamily, source->fontfamily);
  gc->fontface = source->fontface;
  gc->fontsize = source->fontsize;
  gc->lineheight = source->lineheight;
  gc->linetype = source->linetype;
  gc->linewidth = source->linewidth;
  return gc;
}

/* delete a graphics context object */
void gcontext_delete(GContext* gc) {
#ifdef DEBUG_MSG
  Rprintf("gcontext_delete() called.\n");
#endif
  
  Free(gc);
}
 
/* setters/accessors */
void gcontext_set_color(GContext* gc, const char* color) {
  strcpy(gc->color, color);
}

const char* gcontext_color(GContext* gc) {
  return gc->color;
}

void gcontext_set_fill(GContext* gc, const char* color) {
  strcpy(gc->fill, color);
}

const char* gcontext_fill(GContext* gc) {
  return gc->fill;
}

void gcontext_set_fontfamily(GContext* gc, const char* fontfamily) {
  strcpy(gc->fontfamily, fontfamily);
}

const char* gcontext_fontfamily(GContext* gc) {
  return gc->fontfamily;
}

void gcontext_set_fontface(GContext* gc, int fontface) {
  gc->fontface = fontface;
}

int gcontext_fontface(GContext* gc) {
  return gc->fontface;
}

void gcontext_set_fontsize(GContext* gc, double fontsize) {
  gc->fontsize = fontsize;
}

double gcontext_fontsize(GContext* gc) {
  return gc->fontsize;
}

void gcontext_set_lineheight(GContext* gc, double lineheight) {
  gc->lineheight = lineheight;
}

double gcontext_lineheight(GContext* gc) {
  return gc->lineheight;
}

void gcontext_set_linetype(GContext* gc, int linetype) {
  gc->linetype = linetype;
}

int gcontext_linetype(GContext* gc) {
  return gc->linetype;
}

void gcontext_set_linewidth(GContext* gc, double linewidth) {
  gc->linewidth = linewidth;
}

double gcontext_linewidth(GContext* gc) {
  return gc->linewidth;
}
