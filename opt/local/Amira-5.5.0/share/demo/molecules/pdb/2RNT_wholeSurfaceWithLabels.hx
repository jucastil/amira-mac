# Amira Script
if { ![app hasLicense MolecularPack] } { 
	theMsg error "This script requires a MolecularPack license." 
	return 
} 

remove -all
remove physics.icol 2RNT.pdb CompMolSurface 2RNT-surf MolSurfaceView MoleculeLabel

# Create viewers
viewer setVertical 0

viewer 0 show
#viewer 0 setSize 2103 825
viewer 0 setBackgroundMode 1
viewer 0 decoration 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel physics.icol
physics.icol setIconPosition 0 0
physics.icol fire
{physics.icol} setMinMax 0 1
{physics.icol} flags setValue 0
{physics.icol} shift setMinMax -1 1
{physics.icol} shift setValue 0
{physics.icol} scale setMinMax 0 1
{physics.icol} scale setValue 1
physics.icol fire
physics.icol setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/molecules/pdb/2RNT.pdb ] setLabel 2RNT.pdb
2RNT.pdb setIconPosition 20 10
{2RNT.pdb} fire
2RNT.pdb time setMinMax 0 1
2RNT.pdb time setSubMinMax 0 1
2RNT.pdb time setValue 0
2RNT.pdb time setDiscrete 1
2RNT.pdb time setIncrement 1
{2RNT.pdb} transformation setIndex 0 0
{2RNT.pdb} selection setIndex -1
{2RNT.pdb} selection untouch
{2RNT.pdb} selection setOptValue 0 0
{2RNT.pdb} selectionBrowser setIndex -1
{2RNT.pdb} selectionBrowser untouch
{2RNT.pdb} transform setIndex -1
{2RNT.pdb} transform untouch
2RNT.pdb setTransform 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1
2RNT.pdb fire
2RNT.pdb setViewerMask 16383

set hideNewModules 0
create HxCompMolSurface {CompMolSurface}
CompMolSurface setIconPosition 160 10
CompMolSurface Molecule connect 2RNT.pdb
{CompMolSurface} fire
{CompMolSurface} selectAtoms zab HIJMPLPPHPGAAAAAEBMAHHIJ 0
{CompMolSurface} buffer setIndex -1
{CompMolSurface} buffer untouch
{CompMolSurface} buffer setIndex -1
{CompMolSurface} buffer untouch
{CompMolSurface} surfaceType setValue 2
{CompMolSurface} quality setValue 0
{CompMolSurface} probeRadius setMinMax 0.5 3
{CompMolSurface} probeRadius setValue 1.4
{CompMolSurface} edgeLength setMinMax 0.239999994635582 3.40000009536743
{CompMolSurface} edgeLength setValue 0.759836
{CompMolSurface} nopPerA2 setMinMax 0.100000001490116 20
{CompMolSurface} nopPerA2 setValue 2
{CompMolSurface} options setValue 0 0
{CompMolSurface} options setValue 1 0
{CompMolSurface} options setValue 2 0
CompMolSurface filterOptions setValue 0 0
CompMolSurface filterOptions setToggleVisible 0 1
CompMolSurface filterOptions setValue 1 0
CompMolSurface filterOptions setToggleVisible 1 1
{CompMolSurface} doIt setIndex -1
{CompMolSurface} doIt untouch
CompMolSurface fire
CompMolSurface setViewerMask 16383

set hideNewModules 0
[ {CompMolSurface} create
 ] setLabel {2RNT-surf}
2RNT-surf setIconPosition 20 40
2RNT-surf master connect CompMolSurface
2RNT-surf fire
2RNT-surf fire
2RNT-surf setViewerMask 16383

set hideNewModules 0
create HxMolSurfaceView {MolSurfaceView}
MolSurfaceView setIconPosition 274 40
MolSurfaceView data connect 2RNT-surf
{MolSurfaceView} fire
{MolSurfaceView} colormap setDefaultColor 1 0.1 0.1
{MolSurfaceView} colormap setDefaultAlpha 0.500000
MolSurfaceView molecule connect 2RNT.pdb
{MolSurfaceView} continuousColormap setDefaultColor 0 0 1
{MolSurfaceView} continuousColormap setDefaultAlpha 1.000000
{MolSurfaceView} continuousColormap setLocalRange 1
{MolSurfaceView} continuousColormap setLocalMinMax 0.000000 255.000000
{MolSurfaceView} discreteColormap setDefaultColor 0 0 1
{MolSurfaceView} discreteColormap setDefaultAlpha 1.000000
{MolSurfaceView} discreteColormap setLocalRange 1
{MolSurfaceView} discreteColormap setLocalMinMax 1.000000 22.000000
MolSurfaceView discreteColormap connect physics.icol
{MolSurfaceView} fire
{MolSurfaceView} selectAtoms zab HIJMPLPPHPGAAAAAEBMAHHIJ 0
{MolSurfaceView} drawStyle setValue 1
{MolSurfaceView} drawStyle setTexture 0
{MolSurfaceView} drawStyle setNormalBinding 1
{MolSurfaceView} baseTrans setMinMax 0 1
{MolSurfaceView} baseTrans setValue 0.8
{MolSurfaceView} colorMode setValue 1
{MolSurfaceView} defaultColors setColor 0 0.5 0.5 0.5
{MolSurfaceView} defaultColors setColor 1 0.3 0.3 0.8
{MolSurfaceView} pickAction setValue 0
{MolSurfaceView} selectionDistance setMinMax 0.100000001490116 100
{MolSurfaceView} selectionDistance setValue 10
{MolSurfaceView} buffer setIndex -1
{MolSurfaceView} buffer untouch
{MolSurfaceView} highlighting setIndex -1
{MolSurfaceView} highlighting untouch
{MolSurfaceView} buffer setIndex -1
{MolSurfaceView} buffer untouch
{MolSurfaceView} colorscheme setIndex -1
{MolSurfaceView} colorscheme untouch
{MolSurfaceView} colorscheme setOptValue 0 1
{MolSurfaceView} colorscheme setOptValue 1 0
{MolSurfaceView} defineColor setIndex -1
{MolSurfaceView} defineColor untouch
{MolSurfaceView} fire
MolSurfaceView hideBox 1
{MolSurfaceView} selectTriangles zab HIJMONMBABABAAAAAAICKAPPKLGNEIEAABAAAAGPAGADOCPMJO
{MolSurfaceView} fire
{MolSurfaceView} continuousColormap setLocalMinMax 0.000000 255.000000
{MolSurfaceView} discreteColormap setLocalMinMax 1.000000 22.000000
{MolSurfaceView} setScheme Color residues type
MolSurfaceView fire
MolSurfaceView setViewerMask 16383

set hideNewModules 0
create HxMolLabel {MoleculeLabel}
MoleculeLabel setIconPosition 283 10
MoleculeLabel data connect 2RNT.pdb
MoleculeLabel fire
{MoleculeLabel} levels setIndex 0 2
{MoleculeLabel} attributes setIndex 0 0
{MoleculeLabel} attributes setIndex 1 1
{MoleculeLabel} levelOption setValue 0 1
{MoleculeLabel} buttons setIndex -1
{MoleculeLabel} buttons untouch
{MoleculeLabel} fontSize setMinMax 5 30
{MoleculeLabel} fontSize setValue 12
{MoleculeLabel} color setColor 0 0 0 0
{MoleculeLabel} options setValue 0 1
{MoleculeLabel} options setValue 1 1
{MoleculeLabel} setLabelSetInfo 0 1 0.95 0.85 0.1 0 7 14
{MoleculeLabel} setLabelSetInfo 1 1 0.95 0.85 0.1 0 2 14
{MoleculeLabel} setLabelSetInfo 2 1 0 0 0 0 1 12
{MoleculeLabel} setLabelString residues/NIL1 "ALA  NIL1"
{MoleculeLabel} setLabelString residues/NIL2 "CYS  NIL2"
{MoleculeLabel} setLabelString residues/NIL3 "ASP  NIL3"
{MoleculeLabel} setLabelString residues/NIL4 "TYR  NIL4"
{MoleculeLabel} setLabelString residues/NIL5 "THR  NIL5"
{MoleculeLabel} setLabelString residues/NIL6 "CYS  NIL6"
{MoleculeLabel} setLabelString residues/NIL7 "GLY  NIL7"
{MoleculeLabel} setLabelString residues/NIL8 "SER  NIL8"
{MoleculeLabel} setLabelString residues/NIL9 "ASN  NIL9"
{MoleculeLabel} setLabelString residues/NIL10 "CYS  NIL10"
{MoleculeLabel} setLabelString residues/NIL11 "TYR  NIL11"
{MoleculeLabel} setLabelString residues/NIL12 "SER  NIL12"
{MoleculeLabel} setLabelString residues/NIL13 "SER  NIL13"
{MoleculeLabel} setLabelString residues/NIL14 "SER  NIL14"
{MoleculeLabel} setLabelString residues/NIL15 "ASP  NIL15"
{MoleculeLabel} setLabelString residues/NIL16 "VAL  NIL16"
{MoleculeLabel} setLabelString residues/NIL17 "SER  NIL17"
{MoleculeLabel} setLabelString residues/NIL18 "THR  NIL18"
{MoleculeLabel} setLabelString residues/NIL19 "ALA  NIL19"
{MoleculeLabel} setLabelString residues/NIL20 "GLN  NIL20"
{MoleculeLabel} setLabelString residues/NIL21 "ALA  NIL21"
{MoleculeLabel} setLabelString residues/NIL22 "ALA  NIL22"
{MoleculeLabel} setLabelString residues/NIL23 "GLY  NIL23"
{MoleculeLabel} setLabelString residues/NIL24 "TYR  NIL24"
{MoleculeLabel} setLabelString residues/NIL25 "LYS  NIL25"
{MoleculeLabel} setLabelString residues/NIL26 "LEU  NIL26"
{MoleculeLabel} setLabelString residues/NIL27 "HIS  NIL27"
{MoleculeLabel} setLabelString residues/NIL28 "GLU  NIL28"
{MoleculeLabel} setLabelString residues/NIL29 "ASP  NIL29"
{MoleculeLabel} setLabelString residues/NIL30 "GLY  NIL30"
{MoleculeLabel} setLabelString residues/NIL31 "GLU  NIL31"
{MoleculeLabel} setLabelString residues/NIL32 "THR  NIL32"
{MoleculeLabel} setLabelString residues/NIL33 "VAL  NIL33"
{MoleculeLabel} setLabelString residues/NIL34 "GLY  NIL34"
{MoleculeLabel} setLabelString residues/NIL35 "SER  NIL35"
{MoleculeLabel} setLabelString residues/NIL36 "ASN  NIL36"
{MoleculeLabel} setLabelString residues/NIL37 "SER  NIL37"
{MoleculeLabel} setLabelString residues/NIL38 "TYR  NIL38"
{MoleculeLabel} setLabelString residues/NIL39 "PRO  NIL39"
{MoleculeLabel} setLabelString residues/NIL40 "HIS  NIL40"
{MoleculeLabel} setLabelString residues/NIL41 "LYS  NIL41"
{MoleculeLabel} setLabelString residues/NIL42 "TYR  NIL42"
{MoleculeLabel} setLabelString residues/NIL43 "ASN  NIL43"
{MoleculeLabel} setLabelString residues/NIL44 "ASN  NIL44"
{MoleculeLabel} setLabelString residues/NIL45 "TYR  NIL45"
{MoleculeLabel} setLabelString residues/NIL46 "GLU  NIL46"
{MoleculeLabel} setLabelString residues/NIL47 "GLY  NIL47"
{MoleculeLabel} setLabelString residues/NIL48 "PHE  NIL48"
{MoleculeLabel} setLabelString residues/NIL49 "ASP  NIL49"
{MoleculeLabel} setLabelString residues/NIL50 "PHE  NIL50"
{MoleculeLabel} setLabelString residues/NIL51 "SER  NIL51"
{MoleculeLabel} setLabelString residues/NIL52 "VAL  NIL52"
{MoleculeLabel} setLabelString residues/NIL53 "SER  NIL53"
{MoleculeLabel} setLabelString residues/NIL54 "SER  NIL54"
{MoleculeLabel} setLabelString residues/NIL55 "PRO  NIL55"
{MoleculeLabel} setLabelString residues/NIL56 "TYR  NIL56"
{MoleculeLabel} setLabelString residues/NIL57 "TYR  NIL57"
{MoleculeLabel} setLabelString residues/NIL58 "GLU  NIL58"
{MoleculeLabel} setLabelString residues/NIL59 "TRP  NIL59"
{MoleculeLabel} setLabelString residues/NIL60 "PRO  NIL60"
{MoleculeLabel} setLabelString residues/NIL61 "ILE  NIL61"
{MoleculeLabel} setLabelString residues/NIL62 "LEU  NIL62"
{MoleculeLabel} setLabelString residues/NIL63 "SER  NIL63"
{MoleculeLabel} setLabelString residues/NIL64 "SER  NIL64"
{MoleculeLabel} setLabelString residues/NIL65 "GLY  NIL65"
{MoleculeLabel} setLabelString residues/NIL66 "ASP  NIL66"
{MoleculeLabel} setLabelString residues/NIL67 "VAL  NIL67"
{MoleculeLabel} setLabelString residues/NIL68 "TYR  NIL68"
{MoleculeLabel} setLabelString residues/NIL69 "SER  NIL69"
{MoleculeLabel} setLabelString residues/NIL70 "GLY  NIL70"
{MoleculeLabel} setLabelString residues/NIL71 "GLY  NIL71"
{MoleculeLabel} setLabelString residues/NIL72 "SER  NIL72"
{MoleculeLabel} setLabelString residues/NIL73 "PRO  NIL73"
{MoleculeLabel} setLabelString residues/NIL74 "GLY  NIL74"
{MoleculeLabel} setLabelString residues/NIL75 "ALA  NIL75"
{MoleculeLabel} setLabelString residues/NIL76 "ASP  NIL76"
{MoleculeLabel} setLabelString residues/NIL77 "ARG  NIL77"
{MoleculeLabel} setLabelString residues/NIL78 "VAL  NIL78"
{MoleculeLabel} setLabelString residues/NIL79 "VAL  NIL79"
{MoleculeLabel} setLabelString residues/NIL80 "PHE  NIL80"
{MoleculeLabel} setLabelString residues/NIL81 "ASN  NIL81"
{MoleculeLabel} setLabelString residues/NIL82 "GLU  NIL82"
{MoleculeLabel} setLabelString residues/NIL83 "ASN  NIL83"
{MoleculeLabel} setLabelString residues/NIL84 "ASN  NIL84"
{MoleculeLabel} setLabelString residues/NIL85 "GLN  NIL85"
{MoleculeLabel} setLabelString residues/NIL86 "LEU  NIL86"
{MoleculeLabel} setLabelString residues/NIL87 "ALA  NIL87"
{MoleculeLabel} setLabelString residues/NIL88 "GLY  NIL88"
{MoleculeLabel} setLabelString residues/NIL89 "VAL  NIL89"
{MoleculeLabel} setLabelString residues/NIL90 "ILE  NIL90"
{MoleculeLabel} setLabelString residues/NIL91 "THR  NIL91"
{MoleculeLabel} setLabelString residues/NIL92 "HIS  NIL92"
{MoleculeLabel} setLabelString residues/NIL93 "THR  NIL93"
{MoleculeLabel} setLabelString residues/NIL94 "GLY  NIL94"
{MoleculeLabel} setLabelString residues/NIL95 "ALA  NIL95"
{MoleculeLabel} setLabelString residues/NIL96 "SER  NIL96"
{MoleculeLabel} setLabelString residues/NIL97 "GLY  NIL97"
{MoleculeLabel} setLabelString residues/NIL98 "ASN  NIL98"
{MoleculeLabel} setLabelString residues/NIL99 "ASN  NIL99"
{MoleculeLabel} setLabelString residues/NIL100 "PHE  NIL100"
{MoleculeLabel} setLabelString residues/NIL101 "VAL  NIL101"
{MoleculeLabel} setLabelString residues/NIL102 "GLU  NIL102"
{MoleculeLabel} setLabelString residues/NIL103 "CYS  NIL103"
{MoleculeLabel} setLabelString residues/NIL104 "THR  NIL104"
{MoleculeLabel} setLabelString residues/HET105 "GPG  HET105"
{MoleculeLabel} setLabelString residues/HET223 "CA  HET223"
{MoleculeLabel} setLabelString residues/HET106 "HOH  HET106"
{MoleculeLabel} setLabelString residues/HET107 "HOH  HET107"
{MoleculeLabel} setLabelString residues/HET108 "HOH  HET108"
{MoleculeLabel} setLabelString residues/HET109 "HOH  HET109"
{MoleculeLabel} setLabelString residues/HET110 "HOH  HET110"
{MoleculeLabel} setLabelString residues/HET111 "HOH  HET111"
{MoleculeLabel} setLabelString residues/HET112 "HOH  HET112"
{MoleculeLabel} setLabelString residues/HET114 "HOH  HET114"
{MoleculeLabel} setLabelString residues/HET115 "HOH  HET115"
{MoleculeLabel} setLabelString residues/HET116 "HOH  HET116"
{MoleculeLabel} setLabelString residues/HET117 "HOH  HET117"
{MoleculeLabel} setLabelString residues/HET119 "HOH  HET119"
{MoleculeLabel} setLabelString residues/HET120 "HOH  HET120"
{MoleculeLabel} setLabelString residues/HET121 "HOH  HET121"
{MoleculeLabel} setLabelString residues/HET122 "HOH  HET122"
{MoleculeLabel} setLabelString residues/HET124 "HOH  HET124"
{MoleculeLabel} setLabelString residues/HET125 "HOH  HET125"
{MoleculeLabel} setLabelString residues/HET126 "HOH  HET126"
{MoleculeLabel} setLabelString residues/HET127 "HOH  HET127"
{MoleculeLabel} setLabelString residues/HET128 "HOH  HET128"
{MoleculeLabel} setLabelString residues/HET129 "HOH  HET129"
{MoleculeLabel} setLabelString residues/HET130 "HOH  HET130"
{MoleculeLabel} setLabelString residues/HET131 "HOH  HET131"
{MoleculeLabel} setLabelString residues/HET133 "HOH  HET133"
{MoleculeLabel} setLabelString residues/HET134 "HOH  HET134"
{MoleculeLabel} setLabelString residues/HET135 "HOH  HET135"
{MoleculeLabel} setLabelString residues/HET136 "HOH  HET136"
{MoleculeLabel} setLabelString residues/HET138 "HOH  HET138"
{MoleculeLabel} setLabelString residues/HET139 "HOH  HET139"
{MoleculeLabel} setLabelString residues/HET140 "HOH  HET140"
{MoleculeLabel} setLabelString residues/HET142 "HOH  HET142"
{MoleculeLabel} setLabelString residues/HET143 "HOH  HET143"
{MoleculeLabel} setLabelString residues/HET144 "HOH  HET144"
{MoleculeLabel} setLabelString residues/HET145 "HOH  HET145"
{MoleculeLabel} setLabelString residues/HET146 "HOH  HET146"
{MoleculeLabel} setLabelString residues/HET147 "HOH  HET147"
{MoleculeLabel} setLabelString residues/HET148 "HOH  HET148"
{MoleculeLabel} setLabelString residues/HET149 "HOH  HET149"
{MoleculeLabel} setLabelString residues/HET151 "HOH  HET151"
{MoleculeLabel} setLabelString residues/HET152 "HOH  HET152"
{MoleculeLabel} setLabelString residues/HET153 "HOH  HET153"
{MoleculeLabel} setLabelString residues/HET154 "HOH  HET154"
{MoleculeLabel} setLabelString residues/HET155 "HOH  HET155"
{MoleculeLabel} setLabelString residues/HET157 "HOH  HET157"
{MoleculeLabel} setLabelString residues/HET158 "HOH  HET158"
{MoleculeLabel} setLabelString residues/HET159 "HOH  HET159"
{MoleculeLabel} setLabelString residues/HET160 "HOH  HET160"
{MoleculeLabel} setLabelString residues/HET161 "HOH  HET161"
{MoleculeLabel} setLabelString residues/HET162 "HOH  HET162"
{MoleculeLabel} setLabelString residues/HET163 "HOH  HET163"
{MoleculeLabel} setLabelString residues/HET164 "HOH  HET164"
{MoleculeLabel} setLabelString residues/HET165 "HOH  HET165"
{MoleculeLabel} setLabelString residues/HET166 "HOH  HET166"
{MoleculeLabel} setLabelString residues/HET167 "HOH  HET167"
{MoleculeLabel} setLabelString residues/HET168 "HOH  HET168"
{MoleculeLabel} setLabelString residues/HET169 "HOH  HET169"
{MoleculeLabel} setLabelString residues/HET170 "HOH  HET170"
{MoleculeLabel} setLabelString residues/HET172 "HOH  HET172"
{MoleculeLabel} setLabelString residues/HET173 "HOH  HET173"
{MoleculeLabel} setLabelString residues/HET174 "HOH  HET174"
{MoleculeLabel} setLabelString residues/HET176 "HOH  HET176"
{MoleculeLabel} setLabelString residues/HET177 "HOH  HET177"
{MoleculeLabel} setLabelString residues/HET178 "HOH  HET178"
{MoleculeLabel} setLabelString residues/HET181 "HOH  HET181"
{MoleculeLabel} setLabelString residues/HET185 "HOH  HET185"
{MoleculeLabel} setLabelString residues/HET187 "HOH  HET187"
{MoleculeLabel} setLabelString residues/HET189 "HOH  HET189"
{MoleculeLabel} setLabelString residues/HET190 "HOH  HET190"
{MoleculeLabel} setLabelString residues/HET191 "HOH  HET191"
{MoleculeLabel} setLabelString residues/HET192 "HOH  HET192"
{MoleculeLabel} setLabelString residues/HET193 "HOH  HET193"
{MoleculeLabel} setLabelString residues/HET195 "HOH  HET195"
{MoleculeLabel} setLabelString residues/HET198 "HOH  HET198"
{MoleculeLabel} setLabelString residues/HET199 "HOH  HET199"
{MoleculeLabel} setLabelString residues/HET200 "HOH  HET200"
{MoleculeLabel} setLabelString residues/HET203 "HOH  HET203"
{MoleculeLabel} setLabelString residues/HET204 "HOH  HET204"
{MoleculeLabel} setLabelString residues/HET205 "HOH  HET205"
{MoleculeLabel} setLabelString residues/HET206 "HOH  HET206"
{MoleculeLabel} setLabelString residues/HET207 "HOH  HET207"
{MoleculeLabel} setLabelString residues/HET209 "HOH  HET209"
{MoleculeLabel} setLabelString residues/HET210 "HOH  HET210"
{MoleculeLabel} setLabelString residues/HET211 "HOH  HET211"
{MoleculeLabel} setLabelString residues/HET212 "HOH  HET212"
{MoleculeLabel} setLabelString residues/HET213 "HOH  HET213"
{MoleculeLabel} setLabelString residues/HET214 "HOH  HET214"
{MoleculeLabel} setLabelString residues/HET216 "HOH  HET216"
{MoleculeLabel} setLabelString residues/HET217 "HOH  HET217"
{MoleculeLabel} setLabelString residues/HET218 "HOH  HET218"
{MoleculeLabel} setLabelString residues/HET219 "HOH  HET219"
{MoleculeLabel} setLabelString residues/HET221 "HOH  HET221"
{MoleculeLabel} setLabelString residues/HET222 "HOH  HET222"
{MoleculeLabel} setLabelString residues/HET224 "HOH  HET224"
{MoleculeLabel} setLabelString residues/HET225 "HOH  HET225"
{MoleculeLabel} setLabelString residues/HET226 "HOH  HET226"
{MoleculeLabel} setLabelString residues/HET229 "HOH  HET229"
{MoleculeLabel} setLabelString residues/HET230 "HOH  HET230"
{MoleculeLabel} setLabelString residues/HET231 "HOH  HET231"
{MoleculeLabel} setLabelString residues/HET232 "HOH  HET232"
{MoleculeLabel} setLabelString residues/HET233 "HOH  HET233"
{MoleculeLabel} setLabelString residues/HET234 "HOH  HET234"
{MoleculeLabel} setLabelString residues/HET235 "HOH  HET235"
{MoleculeLabel} setLabelString residues/HET238 "HOH  HET238"
{MoleculeLabel} setLabelString residues/HET239 "HOH  HET239"
{MoleculeLabel} setLabelString residues/HET240 "HOH  HET240"
{MoleculeLabel} setLabelString residues/HET241 "HOH  HET241"
{MoleculeLabel} setLabelString residues/HET242 "HOH  HET242"
{MoleculeLabel} setLabelSetInfo 3 1 0.95 0.85 0.1 0 2 14
{MoleculeLabel} setLabelSetInfo 4 1 0.95 0.85 0.1 0 2 14
{MoleculeLabel} setLabelSetInfo 5 1 0.95 0.85 0.1 0 3 14
MoleculeLabel fire
MoleculeLabel setViewerMask 16383
MoleculeLabel select

set hideNewModules 0


viewer 0 setCameraPosition -26.6496 26.0402 -35.8444
viewer 0 setCameraOrientation 0.937402 0.0846477 -0.337804 2.99342
viewer 0 setCameraFocalDistance 69.5611
viewer 0 setAutoRedraw 1
viewer 0 redraw
