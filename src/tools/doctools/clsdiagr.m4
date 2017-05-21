define(class,
`$1MetaCls [label = "$1 Metaclass"];
 $1Cls [label = "$1 Class"]')

define(isa,
`$1 -> $2 [color = Red, style = "dashed"]')

define(super,
`$1 -> $2 [color = Blue]')