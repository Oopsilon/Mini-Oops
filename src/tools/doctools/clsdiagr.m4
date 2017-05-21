divert(`-1')
# foreach(x, (item_1, item_2, ..., item_n), stmt)
#   parenthesized list, simple version
define(`foreach', `pushdef(`$1')_foreach($@)popdef(`$1')')
define(`_arg1', `$1')
define(`_foreach', `ifelse(`$2', `()', `',
  `define(`$1', _arg1$2)$3`'$0(`$1', (shift$2), `$3')')')
divert`'dnl

define(metaClass,
`$1MetaCls [label = "$1 Metaclass"];')

define(class,
`$1Cls [label = "$1 Class"]')

define(isa,
`$1 -> $2 [color = Red, style = "dashed"]')

define(super,
`$1 -> $2 [color = Blue]')

define(classes,
`{
rank="same";'
foreach(`mc', (`$@'), `class(mc) dnl')
`}'
`{
rank="same";'
foreach(`mc', `$@', `metaClass(mc)')
`}')