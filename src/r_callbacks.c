#include "renderer.h"

SEXP get_namespace(const char* namesp) {
  SEXP out, call, namesp_sexp;
  
  PROTECT(namesp_sexp = mkString(namesp));
  PROTECT(call = lang2(install("getNamespace"), namesp_sexp));
  out = eval(call, R_GlobalEnv);
  
  UNPROTECT(2);
  return out;
}

/* Call grid::textGrob() */
SEXP text_grob(SEXP label, SEXP x, SEXP y, SEXP hjust, SEXP vjust, SEXP gp) {
  SEXP out, grid, fun, call, s;
  
  PROTECT(grid = get_namespace("grid"));
  PROTECT(fun = findFun(install("textGrob"), grid));
  
  PROTECT(call = allocVector(LANGSXP, 7)); 
  SETCAR(call, fun);  
  
  s = CDR(call);
  SETCAR(s, label);
  SET_TAG(s, install("label"));
  
  s = CDR(s);
  SETCAR(s, x);
  SET_TAG(s, install("x"));
  
  s = CDR(s);
  SETCAR(s, y);
  SET_TAG(s, install("y"));

  s = CDR(s);
  SETCAR(s, hjust);
  SET_TAG(s, install("hjust"));
  
  s = CDR(s);
  SETCAR(s, vjust);
  SET_TAG(s, install("vjust"));

  s = CDR(s);
  SETCAR(s, gp);
  SET_TAG(s, install("gp"));
  
  out = eval(call, R_GlobalEnv);
  
  UNPROTECT(3);
  return out;
}

/* Call grid::rectGrob() */
SEXP rect_grob(SEXP x, SEXP y, SEXP width, SEXP height, SEXP hjust, SEXP vjust, SEXP gp) {
  SEXP out, grid, fun, call, s;
  
  PROTECT(grid = get_namespace("grid"));
  PROTECT(fun = findFun(install("rectGrob"), grid));
  
  PROTECT(call = allocVector(LANGSXP, 8)); 
  SETCAR(call, fun);  
  
  s = CDR(call);
  SETCAR(s, x);
  SET_TAG(s, install("x"));
  
  s = CDR(s);
  SETCAR(s, y);
  SET_TAG(s, install("y"));

  s = CDR(s);
  SETCAR(s, width);
  SET_TAG(s, install("width"));
  
  s = CDR(s);
  SETCAR(s, height);
  SET_TAG(s, install("height"));
    
  s = CDR(s);
  SETCAR(s, hjust);
  SET_TAG(s, install("hjust"));
  
  s = CDR(s);
  SETCAR(s, vjust);
  SET_TAG(s, install("vjust"));
  
  s = CDR(s);
  SETCAR(s, gp);
  SET_TAG(s, install("gp"));
  
  out = eval(call, R_GlobalEnv);
  
  UNPROTECT(3);
  return out;
}

/* Call grid::linesGrob() */
SEXP lines_grob(SEXP x, SEXP y, SEXP gp) {
  SEXP out, grid, fun, call, s;
  
  PROTECT(grid = get_namespace("grid"));
  PROTECT(fun = findFun(install("linesGrob"), grid));
  
  PROTECT(call = allocVector(LANGSXP, 4)); 
  SETCAR(call, fun);  
  
  s = CDR(call);
  SETCAR(s, x);
  SET_TAG(s, install("x"));
  
  s = CDR(s);
  SETCAR(s, y);
  SET_TAG(s, install("y"));
  
  s = CDR(s);
  SETCAR(s, gp);
  SET_TAG(s, install("gp"));
  
  out = eval(call, R_GlobalEnv);
  
  UNPROTECT(3);
  return out;
}


/* Call grid::unit(x, "inches") */
SEXP unit_in(SEXP x) {
  SEXP out, grid, fun, call, s, unit;
  
  PROTECT(grid = get_namespace("grid"));
  PROTECT(fun = findFun(install("unit"), grid));
  
  PROTECT(call = allocVector(LANGSXP, 3)); 
  SETCAR(call, fun);  
  
  s = CDR(call);
  SETCAR(s, x);

  PROTECT(unit = mkString("inches"));
  s = CDR(s);
  SETCAR(s, unit);
  SET_TAG(s, install("units"));

  out = eval(call, R_GlobalEnv);
  
  UNPROTECT(4);
  return out;
}


/* Call grid::gpar() without any arguments */
SEXP gpar_empty() {
  SEXP out, grid, fun, call;
  
  PROTECT(grid = get_namespace("grid"));
  PROTECT(fun = findFun(install("gpar"), grid));
  PROTECT(call = lang1(fun));
  out = eval(call, R_GlobalEnv);
  
  UNPROTECT(3);
  return out;
}


/* Call grid::gpar() with GR_GContext object */

SEXP gpar_gcontext(const GContext *gc) {
  SEXP out, grid, fun, call, s;
  SEXP col, fill, fontfamily, fontface, fontsize, lineheight,
       linetype, linewidth, lineend;
  
  /* arguments */
  PROTECT(col = mkString(gc->color));
  PROTECT(fill = mkString(gc->fill));
  PROTECT(fontfamily = mkString(gc->fontfamily));
  PROTECT(fontface = ScalarInteger(gc->fontface));
  PROTECT(fontsize = ScalarReal(gc->fontsize));
  PROTECT(lineheight = ScalarReal(gc->lineheight));
  PROTECT(linewidth = ScalarReal(gc->linewidth));

  /* create some custom line types that better much
   * what browsers do.
   */
  switch(gc->linetype) {
  case 2: /* dashed, 2 units on, 1 off */
    PROTECT(linetype = mkString("21"));
    PROTECT(lineend = mkString("butt"));
    break;
  case 3: /* dotted, 1 unit on, 1 off, rounded */
    PROTECT(linetype = mkString("11"));
    PROTECT(lineend = mkString("butt"));
    break;
  default:
    PROTECT(linetype = ScalarInteger(gc->linetype));
    PROTECT(lineend = mkString("butt"));
  } 
    
  /* call */
  PROTECT(grid = get_namespace("grid"));
  PROTECT(fun = findFun(install("gpar"), grid));
  PROTECT(call = allocVector(LANGSXP, 10)); 
  SETCAR(call, fun);  
  
  s = CDR(call);
  SETCAR(s, col);
  SET_TAG(s, install("col"));

  s = CDR(s);
  SETCAR(s, fill);
  SET_TAG(s, install("fill"));
  
  s = CDR(s);
  SETCAR(s, fontfamily);
  SET_TAG(s, install("fontfamily"));
  
  s = CDR(s);
  SETCAR(s, fontface);
  SET_TAG(s, install("fontface"));
  
  s = CDR(s);
  SETCAR(s, fontsize);
  SET_TAG(s, install("fontsize"));
  
  s = CDR(s);
  SETCAR(s, lineheight);
  SET_TAG(s, install("lineheight"));

  s = CDR(s);
  SETCAR(s, linetype);
  SET_TAG(s, install("lty"));
  
  s = CDR(s);
  SETCAR(s, linewidth);
  SET_TAG(s, install("lwd"));
  
  s = CDR(s);
  SETCAR(s, lineend);
  SET_TAG(s, install("lineend"));
  
  out = eval(call, R_GlobalEnv);
  
  UNPROTECT(12);
  return out;
}

/* Test routines */

SEXP test_gpar_gcontext() {
  GContext gc = {
    .color = "red",
    .fill = "#F0F0F0F0",
    .fontfamily = "Helvetica",
    .fontface = 1,
    .fontsize = 12,
    .lineheight = 1.2
  };
  
  return gpar_gcontext(&gc);
}


