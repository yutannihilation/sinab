
<!-- README.md is generated from README.Rmd. Please edit that file -->

# gridtext rewrite

An attempt to rewrite the gridtext package from scratch, with all the
heavy lifting implemented in Rust.

An initial rendering engine has been implemented, though it is for
demonstration purposes only at this time:

``` r
library(grdtext)
library(grid)

css <-
'.brown { color:red; font-family: "Comic Sans MS"; }
em { color:green; }
strong em { color:blue; font-family: monospace; }
strong .brown { color:brown; font-size: 24px; }'

mdtext <-
'The **quick <span class="brown">brown</span>
*fox*** jumps *over* the <span style="color:#0000ff80">lazy
dog.</span><br>The quick <span class="brown">brown</span> fox.'

g <- render_markdown(mdtext, css)
grid.newpage()
grid.draw(g)
```

<img src="man/figures/README-unnamed-chunk-2-1.png" width="100%" />

Simple markdown-to-html conversion is also implemented:

``` r
md_to_html("This is *a* **test**.")
#> [1] "<p>This is <em>a</em> <strong>test</strong>.</p>\n"
```
