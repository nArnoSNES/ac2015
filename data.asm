.include "hdr.asm"

.section ".rodata1" superfree

pattilekawaii: .incbin "rollingbg.pic"
pattilekawaii_end:

maptilekawaii: .incbin "rollingbg.map"
maptilekawaii_end:

paltilekawaii: .incbin "rollingbg.pal"
paltilekawaii_end:

gfxpsrite2: .incbin "sprite2.pic"
gfxpsrite2_end:

palsprite2: .incbin "sprite2.pal"
palsprite2_end:

.ends

.section ".rodata2" superfree

gfxicon: .incbin "menuicon.pic"
gfxicon_end:

palicon: .incbin "menuicon.pal"
palicon_end:

snesfont: .incbin "snesfont.pic"

mapcol2: .incbin "coll2.clm"
mapcol2_end:

.ends

.section ".rodata3" superfree
m0: .incbin "bg0.map"
m0_end:

p0: .incbin "bg0.pal"
p0_end:

t0: .incbin "bg0.pic"
t0_end:

m1: .incbin "bg1.map"
m1_end:

p1: .incbin "bg1.pal"
p1_end:

t1: .incbin "bg1.pic"
t1_end:

m2: .incbin "bg2.map"
m2_end:

p2: .incbin "bg2.pal"
p2_end:

t2: .incbin "bg2.pic"
t2_end:

m3: .incbin "bg3.map"
m3_end:

p3: .incbin "bg3.pal"
p3_end:

t3: .incbin "bg3.pic"
t3_end:

.ends

.section ".rodata4" superfree

gfxaclogo: .incbin "icon.pic"
gfxaclogo_end:

palaclogo: .incbin "icon.pal"
palaclogo_end:

soundbrr: .incbin "hihi.brr"
soundbrrend:

.ends

.section ".rodata5" superfree

patterns: .incbin "ground.pic"
patterns_end:

map: .incbin "ground.map"
map_end:

palette: .incbin "ground.pal"
palette_end:

patterns2: .incbin "ground2.pic"
patterns2_end:

map2: .incbin "ground2.map"
map2_end:

palette2: .incbin "ground2.pal"
palette2_end:

.ends

.section ".rodata6" superfree

mapcol: .incbin "coll.clm"
mapcol_end:

gfxpsrite: .incbin "sprites.pic"
gfxpsrite_end:

palsprite: .incbin "sprites.pal"
palsprite_end:

.ends
