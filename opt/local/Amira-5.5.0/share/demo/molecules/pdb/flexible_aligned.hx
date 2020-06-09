# Amira Script

# test(timeout=130)

if { ![app hasLicense MolecularPack] } { 
	theMsg error "This script requires a MolecularPack license." 
	return 
} 

remove -all
remove 1IGM.pdb 2JEL.pdb AlignSequences AlignPseudoMolecules MoleculeView MoleculeView2 SecStructureView SecStructureView2 SecStructureView3 MoleculeView3

# Create viewers
viewer 0 show
#viewer 0 setSize 824 825
viewer 0 setBackgroundMode 1
viewer 0 decoration 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/molecules/pdb/1IGM.pdb ] setLabel 1IGM.pdb
1IGM.pdb setIconPosition 20 8
{1IGM.pdb} fire
1IGM.pdb time setMinMax 0 1
1IGM.pdb time setSubMinMax 0 1
1IGM.pdb time setValue 0
1IGM.pdb time setDiscrete 1
1IGM.pdb time setIncrement 1
{1IGM.pdb} selectionBrowser setIndex -1
{1IGM.pdb} selectionBrowser untouch
{1IGM.pdb} define seqAlign9/1 residues/L1
{1IGM.pdb} define seqAlign9/2 residues/L2
{1IGM.pdb} define seqAlign9/3 residues/L3
{1IGM.pdb} define seqAlign9/4 residues/L4
{1IGM.pdb} define seqAlign9/5 residues/L5
{1IGM.pdb} define seqAlign9/6 residues/L6
{1IGM.pdb} define seqAlign9/7 residues/L7
{1IGM.pdb} define seqAlign9/8 residues/L8
{1IGM.pdb} define seqAlign9/9 residues/L9
{1IGM.pdb} define seqAlign9/10 residues/L10
{1IGM.pdb} define seqAlign9/11 residues/L11
{1IGM.pdb} define seqAlign9/12 residues/L12
{1IGM.pdb} define seqAlign9/13 residues/L13
{1IGM.pdb} define seqAlign9/14 residues/L14
{1IGM.pdb} define seqAlign9/15 residues/L15
{1IGM.pdb} define seqAlign9/16 residues/L16
{1IGM.pdb} define seqAlign9/17 residues/L17
{1IGM.pdb} define seqAlign9/18 residues/L18
{1IGM.pdb} define seqAlign9/19 residues/L19
{1IGM.pdb} define seqAlign9/20 residues/L20
{1IGM.pdb} define seqAlign9/21 residues/L21
{1IGM.pdb} define seqAlign9/22 residues/L22
{1IGM.pdb} define seqAlign9/23 residues/L23
{1IGM.pdb} define seqAlign9/24 residues/L24
{1IGM.pdb} define seqAlign9/25 residues/L25
{1IGM.pdb} define seqAlign9/26 residues/L26
{1IGM.pdb} define seqAlign9/27 residues/L27
{1IGM.pdb} define seqAlign9/28 residues/L28
{1IGM.pdb} define seqAlign9/29 residues/L29
{1IGM.pdb} define seqAlign9/30 residues/L30
{1IGM.pdb} define seqAlign9/31 residues/L31
{1IGM.pdb} define seqAlign9/32 residues/L32
{1IGM.pdb} define seqAlign9/33 residues/L33
{1IGM.pdb} define seqAlign9/34 residues/L34
{1IGM.pdb} define seqAlign9/35 residues/L35
{1IGM.pdb} define seqAlign9/36 residues/L36
{1IGM.pdb} define seqAlign9/37 residues/L37
{1IGM.pdb} define seqAlign9/38 residues/L38
{1IGM.pdb} define seqAlign9/39 residues/L39
{1IGM.pdb} define seqAlign9/40 residues/L40
{1IGM.pdb} define seqAlign9/41 residues/L41
{1IGM.pdb} define seqAlign9/42 residues/L42
{1IGM.pdb} define seqAlign9/43 residues/L43
{1IGM.pdb} define seqAlign9/44 residues/L44
{1IGM.pdb} define seqAlign9/45 residues/L45
{1IGM.pdb} define seqAlign9/46 residues/L46
{1IGM.pdb} define seqAlign9/47 residues/L47
{1IGM.pdb} define seqAlign9/48 residues/L48
{1IGM.pdb} define seqAlign9/49 residues/L49
{1IGM.pdb} define seqAlign9/50 residues/L50
{1IGM.pdb} define seqAlign9/51 residues/L51
{1IGM.pdb} define seqAlign9/52 residues/L52
{1IGM.pdb} define seqAlign9/53 residues/L53
{1IGM.pdb} define seqAlign9/54 residues/L54
{1IGM.pdb} define seqAlign9/55 residues/L56
{1IGM.pdb} define seqAlign9/56 residues/L57
{1IGM.pdb} define seqAlign9/57 residues/L58
{1IGM.pdb} define seqAlign9/58 residues/L59
{1IGM.pdb} define seqAlign9/59 residues/L60
{1IGM.pdb} define seqAlign9/60 residues/L61
{1IGM.pdb} define seqAlign9/61 residues/L62
{1IGM.pdb} define seqAlign9/62 residues/L63
{1IGM.pdb} define seqAlign9/63 residues/L64
{1IGM.pdb} define seqAlign9/64 residues/L65
{1IGM.pdb} define seqAlign9/65 residues/L66
{1IGM.pdb} define seqAlign9/66 residues/L67
{1IGM.pdb} define seqAlign9/67 residues/L68
{1IGM.pdb} define seqAlign9/68 residues/L69
{1IGM.pdb} define seqAlign9/69 residues/L70
{1IGM.pdb} define seqAlign9/70 residues/L71
{1IGM.pdb} define seqAlign9/71 residues/L72
{1IGM.pdb} define seqAlign9/72 residues/L73
{1IGM.pdb} define seqAlign9/73 residues/L74
{1IGM.pdb} define seqAlign9/74 residues/L75
{1IGM.pdb} define seqAlign9/75 residues/L76
{1IGM.pdb} define seqAlign9/76 residues/L77
{1IGM.pdb} define seqAlign9/77 residues/L78
{1IGM.pdb} define seqAlign9/78 residues/L79
{1IGM.pdb} define seqAlign9/79 residues/L80
{1IGM.pdb} define seqAlign9/80 residues/L81
{1IGM.pdb} define seqAlign9/81 residues/L82
{1IGM.pdb} define seqAlign9/82 residues/L83
{1IGM.pdb} define seqAlign9/83 residues/L84
{1IGM.pdb} define seqAlign9/84 residues/L85
{1IGM.pdb} define seqAlign9/85 residues/L86
{1IGM.pdb} define seqAlign9/86 residues/L87
{1IGM.pdb} define seqAlign9/87 residues/L88
{1IGM.pdb} define seqAlign9/88 residues/L91
{1IGM.pdb} define seqAlign9/89 residues/L92
{1IGM.pdb} define seqAlign9/90 residues/L93
{1IGM.pdb} define seqAlign9/91 residues/L94
{1IGM.pdb} define seqAlign9/92 residues/L95
{1IGM.pdb} define seqAlign9/93 residues/L96
{1IGM.pdb} define seqAlign9/94 residues/L97
{1IGM.pdb} define seqAlign9/95 residues/L98
{1IGM.pdb} define seqAlign9/96 residues/L99
{1IGM.pdb} define seqAlign9/97 residues/L100
{1IGM.pdb} define seqAlign9/98 residues/L101
{1IGM.pdb} define seqAlign9/99 residues/L102
{1IGM.pdb} define seqAlign9/100 residues/L103
{1IGM.pdb} define seqAlign9/101 residues/L104
{1IGM.pdb} define seqAlign9/102 residues/L105
{1IGM.pdb} define seqAlign9/103 residues/L106
{1IGM.pdb} define seqAlign9/104 residues/L107
{1IGM.pdb} define seqAlign9/105 residues/L108
{1IGM.pdb} define seqAlign9/106 residues/L109
{1IGM.pdb} define seqAlign9/107 residues/L110
{1IGM.pdb} define seqAlign9/108 residues/L111
{1IGM.pdb} define seqAlign9/109 residues/L112
{1IGM.pdb} define seqAlign9/110 residues/L113
{1IGM.pdb} define seqAlign9/111 residues/L114
{1IGM.pdb} define seqAlign9/112 residues/L115
{1IGM.pdb} define seqAlign9/113 residues/H1
{1IGM.pdb} define seqAlign9/114 residues/H2
{1IGM.pdb} define seqAlign9/115 residues/H3
{1IGM.pdb} define seqAlign9/116 residues/H4
{1IGM.pdb} define seqAlign9/117 residues/H5
{1IGM.pdb} define seqAlign9/118 residues/H6
{1IGM.pdb} define seqAlign9/119 residues/H7
{1IGM.pdb} define seqAlign9/120 residues/H8
{1IGM.pdb} define seqAlign9/121 residues/H9
{1IGM.pdb} define seqAlign9/122 residues/H10
{1IGM.pdb} define seqAlign9/123 residues/H11
{1IGM.pdb} define seqAlign9/124 residues/H12
{1IGM.pdb} define seqAlign9/125 residues/H13
{1IGM.pdb} define seqAlign9/126 residues/H14
{1IGM.pdb} define seqAlign9/127 residues/H15
{1IGM.pdb} define seqAlign9/128 residues/H16
{1IGM.pdb} define seqAlign9/129 residues/H17
{1IGM.pdb} define seqAlign9/130 residues/H18
{1IGM.pdb} define seqAlign9/131 residues/H19
{1IGM.pdb} define seqAlign9/132 residues/H20
{1IGM.pdb} define seqAlign9/133 residues/H21
{1IGM.pdb} define seqAlign9/134 residues/H22
{1IGM.pdb} define seqAlign9/135 residues/H23
{1IGM.pdb} define seqAlign9/136 residues/H24
{1IGM.pdb} define seqAlign9/137 residues/H25
{1IGM.pdb} define seqAlign9/138 residues/H26
{1IGM.pdb} define seqAlign9/139 residues/H27
{1IGM.pdb} define seqAlign9/140 residues/H28
{1IGM.pdb} define seqAlign9/141 residues/H29
{1IGM.pdb} define seqAlign9/142 residues/H30
{1IGM.pdb} define seqAlign9/143 residues/H31
{1IGM.pdb} define seqAlign9/144 residues/H32
{1IGM.pdb} define seqAlign9/145 residues/H33
{1IGM.pdb} define seqAlign9/146 residues/H34
{1IGM.pdb} define seqAlign9/147 residues/H35
{1IGM.pdb} define seqAlign9/148 residues/H36
{1IGM.pdb} define seqAlign9/149 residues/H37
{1IGM.pdb} define seqAlign9/150 residues/H38
{1IGM.pdb} define seqAlign9/151 residues/H39
{1IGM.pdb} define seqAlign9/152 residues/H40
{1IGM.pdb} define seqAlign9/153 residues/H41
{1IGM.pdb} define seqAlign9/154 residues/H42
{1IGM.pdb} define seqAlign9/155 residues/H43
{1IGM.pdb} define seqAlign9/156 residues/H44
{1IGM.pdb} define seqAlign9/157 residues/H45
{1IGM.pdb} define seqAlign9/158 residues/H46
{1IGM.pdb} define seqAlign9/159 residues/H47
{1IGM.pdb} define seqAlign9/160 residues/H48
{1IGM.pdb} define seqAlign9/161 residues/H50
{1IGM.pdb} define seqAlign9/162 residues/H51
{1IGM.pdb} define seqAlign9/163 residues/H52
{1IGM.pdb} define seqAlign9/164 residues/H54
{1IGM.pdb} define seqAlign9/165 residues/H55
{1IGM.pdb} define seqAlign9/166 residues/H57
{1IGM.pdb} define seqAlign9/167 residues/H58
{1IGM.pdb} define seqAlign9/168 residues/H59
{1IGM.pdb} define seqAlign9/169 residues/H60
{1IGM.pdb} define seqAlign9/170 residues/H61
{1IGM.pdb} define seqAlign9/171 residues/H62
{1IGM.pdb} define seqAlign9/172 residues/H63
{1IGM.pdb} define seqAlign9/173 residues/H64
{1IGM.pdb} define seqAlign9/174 residues/H65
{1IGM.pdb} define seqAlign9/175 residues/H66
{1IGM.pdb} define seqAlign9/176 residues/H67
{1IGM.pdb} define seqAlign9/177 residues/H68
{1IGM.pdb} define seqAlign9/178 residues/H69
{1IGM.pdb} define seqAlign9/179 residues/H70
{1IGM.pdb} define seqAlign9/180 residues/H71
{1IGM.pdb} define seqAlign9/181 residues/H72
{1IGM.pdb} define seqAlign9/182 residues/H73
{1IGM.pdb} define seqAlign9/183 residues/H74
{1IGM.pdb} define seqAlign9/184 residues/H75
{1IGM.pdb} define seqAlign9/185 residues/H76
{1IGM.pdb} define seqAlign9/186 residues/H77
{1IGM.pdb} define seqAlign9/187 residues/H78
{1IGM.pdb} define seqAlign9/188 residues/H79
{1IGM.pdb} define seqAlign9/189 residues/H80
{1IGM.pdb} define seqAlign9/190 residues/H81
{1IGM.pdb} define seqAlign9/191 residues/H82
{1IGM.pdb} define seqAlign9/192 residues/H83
{1IGM.pdb} define seqAlign9/193 residues/H84
{1IGM.pdb} define seqAlign9/194 residues/H85
{1IGM.pdb} define seqAlign9/195 residues/H86
{1IGM.pdb} define seqAlign9/196 residues/H87
{1IGM.pdb} define seqAlign9/197 residues/H88
{1IGM.pdb} define seqAlign9/198 residues/H89
{1IGM.pdb} define seqAlign9/199 residues/H90
{1IGM.pdb} define seqAlign9/200 residues/H91
{1IGM.pdb} define seqAlign9/201 residues/H92
{1IGM.pdb} define seqAlign9/202 residues/H93
{1IGM.pdb} define seqAlign9/203 residues/H94
{1IGM.pdb} define seqAlign9/204 residues/H95
{1IGM.pdb} define seqAlign9/205 residues/H96
{1IGM.pdb} define seqAlign9/206 residues/H97
{1IGM.pdb} define seqAlign9/207 residues/H100
{1IGM.pdb} define seqAlign9/208 residues/H101
{1IGM.pdb} define seqAlign9/209 residues/H105
{1IGM.pdb} define seqAlign9/210 residues/H107
{1IGM.pdb} define seqAlign9/211 residues/H108
{1IGM.pdb} define seqAlign9/212 residues/H109
{1IGM.pdb} define seqAlign9/213 residues/H110
{1IGM.pdb} define seqAlign9/214 residues/H111
{1IGM.pdb} define seqAlign9/215 residues/H112
{1IGM.pdb} define seqAlign9/216 residues/H113
{1IGM.pdb} define seqAlign9/217 residues/H114
{1IGM.pdb} define seqAlign9/218 residues/H115
{1IGM.pdb} define seqAlign9/219 residues/H116
{1IGM.pdb} define seqAlign9/220 residues/H117
{1IGM.pdb} define seqAlign9/221 residues/H118
{1IGM.pdb} define seqAlign9/222 residues/H119
{1IGM.pdb} define seqAlign9/223 residues/H120
{1IGM.pdb} define seqAlign9/224 residues/H121
{1IGM.pdb} define seqAlign9/225 residues/H123
{1IGM.pdb} define seqAlign9/226 residues/H124
{1IGM.pdb} define seqAlign9/227 residues/H125
{1IGM.pdb} define seqAlign9/228 residues/H126
{1IGM.pdb} define seqAlign9/229 residues/H127
{1IGM.pdb} define seqAlign9/230 residues/H128
{1IGM.pdb} define seqAlign9/231 residues/H129
1IGM.pdb fire
1IGM.pdb setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/molecules/pdb/2JEL.pdb ] setLabel 2JEL.pdb
2JEL.pdb setIconPosition 20 153
{2JEL.pdb} fire
2JEL.pdb time setMinMax 0 1
2JEL.pdb time setSubMinMax 0 1
2JEL.pdb time setValue 0
2JEL.pdb time setDiscrete 1
2JEL.pdb time setIncrement 1
{2JEL.pdb} selectionBrowser setIndex -1
{2JEL.pdb} selectionBrowser untouch
{2JEL.pdb} define seqAlign9/1 residues/L1
{2JEL.pdb} define seqAlign9/2 residues/L2
{2JEL.pdb} define seqAlign9/3 residues/L3
{2JEL.pdb} define seqAlign9/4 residues/L4
{2JEL.pdb} define seqAlign9/5 residues/L5
{2JEL.pdb} define seqAlign9/6 residues/L6
{2JEL.pdb} define seqAlign9/7 residues/L7
{2JEL.pdb} define seqAlign9/8 residues/L8
{2JEL.pdb} define seqAlign9/9 residues/L9
{2JEL.pdb} define seqAlign9/10 residues/L10
{2JEL.pdb} define seqAlign9/11 residues/L11
{2JEL.pdb} define seqAlign9/12 residues/L12
{2JEL.pdb} define seqAlign9/13 residues/L13
{2JEL.pdb} define seqAlign9/14 residues/L14
{2JEL.pdb} define seqAlign9/15 residues/L15
{2JEL.pdb} define seqAlign9/16 residues/L16
{2JEL.pdb} define seqAlign9/17 residues/L17
{2JEL.pdb} define seqAlign9/18 residues/L18
{2JEL.pdb} define seqAlign9/19 residues/L19
{2JEL.pdb} define seqAlign9/20 residues/L20
{2JEL.pdb} define seqAlign9/21 residues/L21
{2JEL.pdb} define seqAlign9/22 residues/L22
{2JEL.pdb} define seqAlign9/23 residues/L23
{2JEL.pdb} define seqAlign9/24 residues/L24
{2JEL.pdb} define seqAlign9/25 residues/L25
{2JEL.pdb} define seqAlign9/26 residues/L26
{2JEL.pdb} define seqAlign9/27 residues/L27
{2JEL.pdb} define seqAlign9/28 residues/L27A
{2JEL.pdb} define seqAlign9/29 residues/L27B
{2JEL.pdb} define seqAlign9/30 residues/L28
{2JEL.pdb} define seqAlign9/31 residues/L30
{2JEL.pdb} define seqAlign9/32 residues/L32
{2JEL.pdb} define seqAlign9/33 residues/L33
{2JEL.pdb} define seqAlign9/34 residues/L34
{2JEL.pdb} define seqAlign9/35 residues/L35
{2JEL.pdb} define seqAlign9/36 residues/L36
{2JEL.pdb} define seqAlign9/37 residues/L37
{2JEL.pdb} define seqAlign9/38 residues/L38
{2JEL.pdb} define seqAlign9/39 residues/L39
{2JEL.pdb} define seqAlign9/40 residues/L40
{2JEL.pdb} define seqAlign9/41 residues/L41
{2JEL.pdb} define seqAlign9/42 residues/L42
{2JEL.pdb} define seqAlign9/43 residues/L43
{2JEL.pdb} define seqAlign9/44 residues/L44
{2JEL.pdb} define seqAlign9/45 residues/L45
{2JEL.pdb} define seqAlign9/46 residues/L46
{2JEL.pdb} define seqAlign9/47 residues/L47
{2JEL.pdb} define seqAlign9/48 residues/L48
{2JEL.pdb} define seqAlign9/49 residues/L49
{2JEL.pdb} define seqAlign9/50 residues/L50
{2JEL.pdb} define seqAlign9/51 residues/L51
{2JEL.pdb} define seqAlign9/52 residues/L52
{2JEL.pdb} define seqAlign9/53 residues/L53
{2JEL.pdb} define seqAlign9/54 residues/L55
{2JEL.pdb} define seqAlign9/55 residues/L56
{2JEL.pdb} define seqAlign9/56 residues/L57
{2JEL.pdb} define seqAlign9/57 residues/L58
{2JEL.pdb} define seqAlign9/58 residues/L59
{2JEL.pdb} define seqAlign9/59 residues/L60
{2JEL.pdb} define seqAlign9/60 residues/L61
{2JEL.pdb} define seqAlign9/61 residues/L62
{2JEL.pdb} define seqAlign9/62 residues/L63
{2JEL.pdb} define seqAlign9/63 residues/L64
{2JEL.pdb} define seqAlign9/64 residues/L65
{2JEL.pdb} define seqAlign9/65 residues/L66
{2JEL.pdb} define seqAlign9/66 residues/L67
{2JEL.pdb} define seqAlign9/67 residues/L68
{2JEL.pdb} define seqAlign9/68 residues/L69
{2JEL.pdb} define seqAlign9/69 residues/L70
{2JEL.pdb} define seqAlign9/70 residues/L71
{2JEL.pdb} define seqAlign9/71 residues/L72
{2JEL.pdb} define seqAlign9/72 residues/L73
{2JEL.pdb} define seqAlign9/73 residues/L74
{2JEL.pdb} define seqAlign9/74 residues/L75
{2JEL.pdb} define seqAlign9/75 residues/L76
{2JEL.pdb} define seqAlign9/76 residues/L77
{2JEL.pdb} define seqAlign9/77 residues/L78
{2JEL.pdb} define seqAlign9/78 residues/L79
{2JEL.pdb} define seqAlign9/79 residues/L80
{2JEL.pdb} define seqAlign9/80 residues/L81
{2JEL.pdb} define seqAlign9/81 residues/L82
{2JEL.pdb} define seqAlign9/82 residues/L83
{2JEL.pdb} define seqAlign9/83 residues/L84
{2JEL.pdb} define seqAlign9/84 residues/L85
{2JEL.pdb} define seqAlign9/85 residues/L86
{2JEL.pdb} define seqAlign9/86 residues/L87
{2JEL.pdb} define seqAlign9/87 residues/L88
{2JEL.pdb} define seqAlign9/88 residues/L89
{2JEL.pdb} define seqAlign9/89 residues/L90
{2JEL.pdb} define seqAlign9/90 residues/L93
{2JEL.pdb} define seqAlign9/91 residues/L94
{2JEL.pdb} define seqAlign9/92 residues/L95
{2JEL.pdb} define seqAlign9/93 residues/L96
{2JEL.pdb} define seqAlign9/94 residues/L97
{2JEL.pdb} define seqAlign9/95 residues/L98
{2JEL.pdb} define seqAlign9/96 residues/L99
{2JEL.pdb} define seqAlign9/97 residues/L100
{2JEL.pdb} define seqAlign9/98 residues/L101
{2JEL.pdb} define seqAlign9/99 residues/L102
{2JEL.pdb} define seqAlign9/100 residues/L103
{2JEL.pdb} define seqAlign9/101 residues/L104
{2JEL.pdb} define seqAlign9/102 residues/L105
{2JEL.pdb} define seqAlign9/103 residues/L106
{2JEL.pdb} define seqAlign9/104 residues/L107
{2JEL.pdb} define seqAlign9/105 residues/L108
{2JEL.pdb} define seqAlign9/106 residues/L109
{2JEL.pdb} define seqAlign9/107 residues/L110
{2JEL.pdb} define seqAlign9/108 residues/L111
{2JEL.pdb} define seqAlign9/109 residues/L112
{2JEL.pdb} define seqAlign9/110 residues/L113
{2JEL.pdb} define seqAlign9/111 residues/L116
{2JEL.pdb} define seqAlign9/112 residues/L117
{2JEL.pdb} define seqAlign9/113 residues/L123
{2JEL.pdb} define seqAlign9/114 residues/L133
{2JEL.pdb} define seqAlign9/115 residues/L135
{2JEL.pdb} define seqAlign9/116 residues/L136
{2JEL.pdb} define seqAlign9/117 residues/L144
{2JEL.pdb} define seqAlign9/118 residues/L147
{2JEL.pdb} define seqAlign9/119 residues/L149
{2JEL.pdb} define seqAlign9/120 residues/L151
{2JEL.pdb} define seqAlign9/121 residues/L153
{2JEL.pdb} define seqAlign9/122 residues/L157
{2JEL.pdb} define seqAlign9/123 residues/L160
{2JEL.pdb} define seqAlign9/124 residues/L164
{2JEL.pdb} define seqAlign9/125 residues/L166
{2JEL.pdb} define seqAlign9/126 residues/L204
{2JEL.pdb} define seqAlign9/127 residues/H8
{2JEL.pdb} define seqAlign9/128 residues/H15
{2JEL.pdb} define seqAlign9/129 residues/H17
{2JEL.pdb} define seqAlign9/130 residues/H18
{2JEL.pdb} define seqAlign9/131 residues/H19
{2JEL.pdb} define seqAlign9/132 residues/H20
{2JEL.pdb} define seqAlign9/133 residues/H21
{2JEL.pdb} define seqAlign9/134 residues/H22
{2JEL.pdb} define seqAlign9/135 residues/H23
{2JEL.pdb} define seqAlign9/136 residues/H24
{2JEL.pdb} define seqAlign9/137 residues/H25
{2JEL.pdb} define seqAlign9/138 residues/H26
{2JEL.pdb} define seqAlign9/139 residues/H27
{2JEL.pdb} define seqAlign9/140 residues/H28
{2JEL.pdb} define seqAlign9/141 residues/H29
{2JEL.pdb} define seqAlign9/142 residues/H30
{2JEL.pdb} define seqAlign9/143 residues/H31
{2JEL.pdb} define seqAlign9/144 residues/H32
{2JEL.pdb} define seqAlign9/145 residues/H33
{2JEL.pdb} define seqAlign9/146 residues/H34
{2JEL.pdb} define seqAlign9/147 residues/H35
{2JEL.pdb} define seqAlign9/148 residues/H36
{2JEL.pdb} define seqAlign9/149 residues/H37
{2JEL.pdb} define seqAlign9/150 residues/H38
{2JEL.pdb} define seqAlign9/151 residues/H39
{2JEL.pdb} define seqAlign9/152 residues/H40
{2JEL.pdb} define seqAlign9/153 residues/H41
{2JEL.pdb} define seqAlign9/154 residues/H42
{2JEL.pdb} define seqAlign9/155 residues/H43
{2JEL.pdb} define seqAlign9/156 residues/H44
{2JEL.pdb} define seqAlign9/157 residues/H45
{2JEL.pdb} define seqAlign9/158 residues/H46
{2JEL.pdb} define seqAlign9/159 residues/H47
{2JEL.pdb} define seqAlign9/160 residues/H48
{2JEL.pdb} define seqAlign9/161 residues/H49
{2JEL.pdb} define seqAlign9/162 residues/H51
{2JEL.pdb} define seqAlign9/163 residues/H53
{2JEL.pdb} define seqAlign9/164 residues/H54
{2JEL.pdb} define seqAlign9/165 residues/H55
{2JEL.pdb} define seqAlign9/166 residues/H56
{2JEL.pdb} define seqAlign9/167 residues/H57
{2JEL.pdb} define seqAlign9/168 residues/H58
{2JEL.pdb} define seqAlign9/169 residues/H59
{2JEL.pdb} define seqAlign9/170 residues/H60
{2JEL.pdb} define seqAlign9/171 residues/H61
{2JEL.pdb} define seqAlign9/172 residues/H62
{2JEL.pdb} define seqAlign9/173 residues/H63
{2JEL.pdb} define seqAlign9/174 residues/H64
{2JEL.pdb} define seqAlign9/175 residues/H65
{2JEL.pdb} define seqAlign9/176 residues/H66
{2JEL.pdb} define seqAlign9/177 residues/H67
{2JEL.pdb} define seqAlign9/178 residues/H68
{2JEL.pdb} define seqAlign9/179 residues/H69
{2JEL.pdb} define seqAlign9/180 residues/H70
{2JEL.pdb} define seqAlign9/181 residues/H71
{2JEL.pdb} define seqAlign9/182 residues/H72
{2JEL.pdb} define seqAlign9/183 residues/H73
{2JEL.pdb} define seqAlign9/184 residues/H74
{2JEL.pdb} define seqAlign9/185 residues/H75
{2JEL.pdb} define seqAlign9/186 residues/H76
{2JEL.pdb} define seqAlign9/187 residues/H77
{2JEL.pdb} define seqAlign9/188 residues/H78
{2JEL.pdb} define seqAlign9/189 residues/H79
{2JEL.pdb} define seqAlign9/190 residues/H80
{2JEL.pdb} define seqAlign9/191 residues/H81
{2JEL.pdb} define seqAlign9/192 residues/H82
{2JEL.pdb} define seqAlign9/193 residues/H82A
{2JEL.pdb} define seqAlign9/194 residues/H82B
{2JEL.pdb} define seqAlign9/195 residues/H82C
{2JEL.pdb} define seqAlign9/196 residues/H83
{2JEL.pdb} define seqAlign9/197 residues/H84
{2JEL.pdb} define seqAlign9/198 residues/H85
{2JEL.pdb} define seqAlign9/199 residues/H86
{2JEL.pdb} define seqAlign9/200 residues/H87
{2JEL.pdb} define seqAlign9/201 residues/H88
{2JEL.pdb} define seqAlign9/202 residues/H89
{2JEL.pdb} define seqAlign9/203 residues/H90
{2JEL.pdb} define seqAlign9/204 residues/H91
{2JEL.pdb} define seqAlign9/205 residues/H92
{2JEL.pdb} define seqAlign9/206 residues/H93
{2JEL.pdb} define seqAlign9/207 residues/H94
{2JEL.pdb} define seqAlign9/208 residues/H95
{2JEL.pdb} define seqAlign9/209 residues/H96
{2JEL.pdb} define seqAlign9/210 residues/H97
{2JEL.pdb} define seqAlign9/211 residues/H100A
{2JEL.pdb} define seqAlign9/212 residues/H101
{2JEL.pdb} define seqAlign9/213 residues/H102
{2JEL.pdb} define seqAlign9/214 residues/H103
{2JEL.pdb} define seqAlign9/215 residues/H104
{2JEL.pdb} define seqAlign9/216 residues/H105
{2JEL.pdb} define seqAlign9/217 residues/H106
{2JEL.pdb} define seqAlign9/218 residues/H107
{2JEL.pdb} define seqAlign9/219 residues/H108
{2JEL.pdb} define seqAlign9/220 residues/H109
{2JEL.pdb} define seqAlign9/221 residues/H110
{2JEL.pdb} define seqAlign9/222 residues/H111
{2JEL.pdb} define seqAlign9/223 residues/H112
{2JEL.pdb} define seqAlign9/224 residues/H113
{2JEL.pdb} define seqAlign9/225 residues/H114
{2JEL.pdb} define seqAlign9/226 residues/H115
{2JEL.pdb} define seqAlign9/227 residues/H116
{2JEL.pdb} define seqAlign9/228 residues/H117
{2JEL.pdb} define seqAlign9/229 residues/H119
{2JEL.pdb} define seqAlign9/230 residues/H120
{2JEL.pdb} define seqAlign9/231 residues/H121
2JEL.pdb fire
2JEL.pdb setViewerMask 16383

set hideNewModules 0
create HxSeqAlign {AlignSequences}
AlignSequences setIconPosition 160 10
AlignSequences MoleculeA connect 1IGM.pdb
AlignSequences moleculeB connect 2JEL.pdb
AlignSequences fire
{AlignSequences} options setValue 0 0
{AlignSequences} input setValue 0
{AlignSequences} motif setValue ""
{AlignSequences} alignType setIndex 0 0
{AlignSequences} alignType setIndex 1 1
{AlignSequences} doIt hit
AlignSequences fire
AlignSequences setViewerMask 16383

set hideNewModules 0
create HxAlignMolecules {AlignMolecules}
AlignMolecules setIconPosition 157 94
AlignMolecules moleculeA connect 1IGM.pdb
AlignMolecules moleculeB connect 2JEL.pdb
AlignMolecules fire
{AlignMolecules} mode setValue 1
{AlignMolecules} options setValue 0 0
{AlignMolecules} options setValue 1 0
{AlignMolecules} transforms setMinMax 0 0
{AlignMolecules} transforms setValue 0
{AlignMolecules} alignLevel setIndex 0 1
{AlignMolecules} doIt setIndex -1
{AlignMolecules} doIt hit
AlignMolecules fire
AlignMolecules setViewerMask 16383
AlignMolecules select

set hideNewModules 0
create HxMolView {MoleculeView}
MoleculeView setIconPosition 286 9
MoleculeView data connect 1IGM.pdb
{MoleculeView} continuousColormap setDefaultColor 0 0 1
{MoleculeView} continuousColormap setDefaultAlpha 1.000000
{MoleculeView} discreteColormap setDefaultColor 1 0.917697 0.224
{MoleculeView} discreteColormap setDefaultAlpha 1.000000
{MoleculeView} fire
{MoleculeView} setBackboneMode 0 1
{MoleculeView} selectAtoms zab HIJMGDGAMAAEPPEBBIAIBIBINIPPGDJBBOJEOAPPPPADGADHIDNNMNPMJPCIHHADAAILAHBCLJ
{MoleculeView} mode setValue 2
{MoleculeView} quality setValue 0
{MoleculeView} options setValue 0 0
{MoleculeView} options setValue 1 0
{MoleculeView} options setValue 2 0
{MoleculeView} atomRadius setMinMax 0 2
{MoleculeView} atomRadius setValue 0.3
{MoleculeView} bondRadius setMinMax 0 0.5
{MoleculeView} bondRadius setValue 0.05
{MoleculeView} lineWidth setMinMax 1 3
{MoleculeView} lineWidth setValue 2
{MoleculeView} complexity setMinMax 0 1
{MoleculeView} complexity setValue 0.2
{MoleculeView} twistFactor setMinMax 0.5 2
{MoleculeView} twistFactor setValue 1
{MoleculeView} colorscheme setOptValue 0 1
{MoleculeView} colorscheme setOptValue 1 0
{MoleculeView} buffer setIndex -1
{MoleculeView} buffer untouch
MoleculeView fire
MoleculeView setViewerMask 16383

set hideNewModules 0
create HxMolView {MoleculeView2}
MoleculeView2 setIconPosition 277 156
MoleculeView2 data connect 2JEL.pdb
{MoleculeView2} continuousColormap setDefaultColor 0 0 1
{MoleculeView2} continuousColormap setDefaultAlpha 1.000000
{MoleculeView2} discreteColormap setDefaultColor 0.639522 0 0.82
{MoleculeView2} discreteColormap setDefaultAlpha 1.000000
{MoleculeView2} fire
{MoleculeView2} setBackboneMode 0 1
{MoleculeView2} selectAtoms zab HIJMGDGAMAAONIPJPPPPJAJBDNHIIHIBEBPOBPAOCFCDAODMAAOCPPFAMAMAMAPPHPKANNEDAJAAAANOAJAOOH
{MoleculeView2} mode setValue 2
{MoleculeView2} quality setValue 0
{MoleculeView2} options setValue 0 0
{MoleculeView2} options setValue 1 0
{MoleculeView2} options setValue 2 0
{MoleculeView2} atomRadius setMinMax 0 2
{MoleculeView2} atomRadius setValue 0.3
{MoleculeView2} bondRadius setMinMax 0 0.5
{MoleculeView2} bondRadius setValue 0.05
{MoleculeView2} lineWidth setMinMax 1 3
{MoleculeView2} lineWidth setValue 2
{MoleculeView2} complexity setMinMax 0 1
{MoleculeView2} complexity setValue 0.2
{MoleculeView2} twistFactor setMinMax 0.5 2
{MoleculeView2} twistFactor setValue 1
{MoleculeView2} colorscheme setOptValue 0 1
{MoleculeView2} colorscheme setOptValue 1 0
{MoleculeView2} buffer setIndex -1
{MoleculeView2} buffer untouch
MoleculeView2 fire
MoleculeView2 setViewerMask 16383

set hideNewModules 0
create HxSecStructure {SecStructureView}
SecStructureView setIconPosition 268 39
SecStructureView data connect 1IGM.pdb
{SecStructureView} discreteColormapBB setDefaultColor 0.78 0.78 0.78
{SecStructureView} discreteColormapBB setDefaultAlpha 1.000000
{SecStructureView} discreteColormapBB setLocalRange 1
{SecStructureView} discreteColormapBB setLocalMinMax 0.000000 20.000000
{SecStructureView} continuousColormapBB setDefaultColor 1 0.917647 0.223529
{SecStructureView} continuousColormapBB setDefaultAlpha 1.000000
{SecStructureView} continuousColormapBB setLocalRange 1
{SecStructureView} continuousColormapBB setLocalMinMax 0.000000 20.000000
{SecStructureView} discreteColormapH setDefaultColor 0.3 0.3 0.9
{SecStructureView} discreteColormapH setDefaultAlpha 1.000000
{SecStructureView} discreteColormapH setLocalRange 1
{SecStructureView} discreteColormapH setLocalMinMax 0.000000 20.000000
{SecStructureView} continuousColormapH setDefaultColor 0.3 0.3 0.9
{SecStructureView} continuousColormapH setDefaultAlpha 1.000000
{SecStructureView} continuousColormapH setLocalRange 1
{SecStructureView} continuousColormapH setLocalMinMax 0.000000 20.000000
{SecStructureView} discreteColormapS setDefaultColor 0.9 0.2 0.2
{SecStructureView} discreteColormapS setDefaultAlpha 1.000000
{SecStructureView} discreteColormapS setLocalRange 1
{SecStructureView} discreteColormapS setLocalMinMax 0.000000 20.000000
{SecStructureView} continuousColormapS setDefaultColor 0.9 0.2 0.2
{SecStructureView} continuousColormapS setDefaultAlpha 1.000000
{SecStructureView} continuousColormapS setLocalRange 1
{SecStructureView} continuousColormapS setLocalMinMax 0.000000 20.000000
{SecStructureView} discreteColormapT setDefaultColor 0.4 0.4 0.4
{SecStructureView} discreteColormapT setDefaultAlpha 1.000000
{SecStructureView} discreteColormapT setLocalRange 1
{SecStructureView} discreteColormapT setLocalMinMax 0.000000 20.000000
{SecStructureView} continuousColormapT setDefaultColor 1 0.917647 0.223529
{SecStructureView} continuousColormapT setDefaultAlpha 1.000000
{SecStructureView} continuousColormapT setLocalRange 1
{SecStructureView} continuousColormapT setLocalMinMax 0.000000 20.000000
{SecStructureView} fire
{SecStructureView} selectAtoms zab HIJMPLPPHPOEACAABBLKPLAF
{SecStructureView} generalShape setValue 0
{SecStructureView} generalThreadsWidth setMinMax 0.5 4
{SecStructureView} generalThreadsWidth setValue 2
{SecStructureView} generalRibbonWidth setMinMax 0.5 4
{SecStructureView} generalRibbonWidth setValue 2
{SecStructureView} options setValue 0
{SecStructureView} backboneTubeRadius setMinMax 0.100000001490116 0.5
{SecStructureView} backboneTubeRadius setValue 0.2
{SecStructureView} colorschemeBB setIndex -1
{SecStructureView} colorschemeBB untouch
{SecStructureView} colorschemeBB setOptValue 0 0
{SecStructureView} colorschemeBB setOptValue 1 0
{SecStructureView} helixShape setValue 1
{SecStructureView} helixTubeRadius setMinMax 0.100000001490116 2
{SecStructureView} helixTubeRadius setValue 0.5
{SecStructureView} helixCylinderRadius setMinMax 0.100000001490116 4
{SecStructureView} helixCylinderRadius setValue 2.1
{SecStructureView} helixRibbonWidth setMinMax 0.5 2
{SecStructureView} helixRibbonWidth setValue 1
{SecStructureView} colorschemeH setIndex -1
{SecStructureView} colorschemeH untouch
{SecStructureView} colorschemeH setOptValue 0 0
{SecStructureView} colorschemeH setOptValue 1 0
{SecStructureView} sheetShape setValue 1
{SecStructureView} sheetArrowWidth setMinMax 0.5 5
{SecStructureView} sheetArrowWidth setValue 1.5
{SecStructureView} sheetArrowOptions setValue 0 1
{SecStructureView} sheetArrowOptions setValue 1 1
{SecStructureView} sheetArrowOptions setValue 2 1
{SecStructureView} sheetRadius setMinMax 0.100000001490116 2
{SecStructureView} sheetRadius setValue 0.3
{SecStructureView} colorschemeS setIndex -1
{SecStructureView} colorschemeS untouch
{SecStructureView} colorschemeS setOptValue 0 0
{SecStructureView} colorschemeS setOptValue 1 0
{SecStructureView} turnTubeRadius setMinMax 0.100000001490116 2
{SecStructureView} turnTubeRadius setValue 0.3
{SecStructureView} colorschemeT setIndex -1
{SecStructureView} colorschemeT untouch
{SecStructureView} colorschemeT setOptValue 0 0
{SecStructureView} colorschemeT setOptValue 1 0
{SecStructureView} structures setValue 0 1
{SecStructureView} structures setValue 1 0
{SecStructureView} structures setValue 2 0
{SecStructureView} structures setValue 3 0
{SecStructureView} complexity setMinMax 0 1
{SecStructureView} complexity setValue 0.5
{SecStructureView} buffer setIndex -1
{SecStructureView} buffer untouch
{SecStructureView} fire
{SecStructureView} discreteColormapBB setLocalMinMax 0.000000 20.000000
{SecStructureView} continuousColormapBB setLocalMinMax 0.000000 20.000000
{SecStructureView} discreteColormapH setLocalMinMax 0.000000 20.000000
{SecStructureView} continuousColormapH setLocalMinMax 0.000000 20.000000
{SecStructureView} discreteColormapS setLocalMinMax 0.000000 20.000000
{SecStructureView} continuousColormapS setLocalMinMax 0.000000 20.000000
{SecStructureView} discreteColormapT setLocalMinMax 0.000000 20.000000
{SecStructureView} continuousColormapT setLocalMinMax 0.000000 20.000000
SecStructureView fire
SecStructureView setViewerMask 16383

set hideNewModules 0
create HxSecStructure {SecStructureView2}
SecStructureView2 setIconPosition 259 183
SecStructureView2 data connect 2JEL.pdb
{SecStructureView2} discreteColormapBB setDefaultColor 0.78 0.78 0.78
{SecStructureView2} discreteColormapBB setDefaultAlpha 1.000000
{SecStructureView2} discreteColormapBB setLocalRange 1
{SecStructureView2} discreteColormapBB setLocalMinMax 0.000000 21.000000
{SecStructureView2} continuousColormapBB setDefaultColor 0.639216 0 0.819608
{SecStructureView2} continuousColormapBB setDefaultAlpha 1.000000
{SecStructureView2} continuousColormapBB setLocalRange 1
{SecStructureView2} continuousColormapBB setLocalMinMax 0.000000 21.000000
{SecStructureView2} discreteColormapH setDefaultColor 0.3 0.3 0.9
{SecStructureView2} discreteColormapH setDefaultAlpha 1.000000
{SecStructureView2} discreteColormapH setLocalRange 1
{SecStructureView2} discreteColormapH setLocalMinMax 0.000000 21.000000
{SecStructureView2} continuousColormapH setDefaultColor 0.3 0.3 0.9
{SecStructureView2} continuousColormapH setDefaultAlpha 1.000000
{SecStructureView2} continuousColormapH setLocalRange 1
{SecStructureView2} continuousColormapH setLocalMinMax 0.000000 21.000000
{SecStructureView2} discreteColormapS setDefaultColor 0.9 0.2 0.2
{SecStructureView2} discreteColormapS setDefaultAlpha 1.000000
{SecStructureView2} discreteColormapS setLocalRange 1
{SecStructureView2} discreteColormapS setLocalMinMax 0.000000 21.000000
{SecStructureView2} continuousColormapS setDefaultColor 0.9 0.2 0.2
{SecStructureView2} continuousColormapS setDefaultAlpha 1.000000
{SecStructureView2} continuousColormapS setLocalRange 1
{SecStructureView2} continuousColormapS setLocalMinMax 0.000000 21.000000
{SecStructureView2} discreteColormapT setDefaultColor 0.4 0.4 0.4
{SecStructureView2} discreteColormapT setDefaultAlpha 1.000000
{SecStructureView2} discreteColormapT setLocalRange 1
{SecStructureView2} discreteColormapT setLocalMinMax 0.000000 21.000000
{SecStructureView2} continuousColormapT setDefaultColor 0.4 0.4 0.4
{SecStructureView2} continuousColormapT setDefaultAlpha 1.000000
{SecStructureView2} continuousColormapT setLocalRange 1
{SecStructureView2} continuousColormapT setLocalMinMax 0.000000 21.000000
{SecStructureView2} fire
{SecStructureView2} selectAtoms zab HIJMPLPPHPBEAMFGMAMAMAMAMIEAEFAADEPCBPMMGMAAPBJGKGGI
{SecStructureView2} generalShape setValue 0
{SecStructureView2} generalThreadsWidth setMinMax 0.5 4
{SecStructureView2} generalThreadsWidth setValue 2
{SecStructureView2} generalRibbonWidth setMinMax 0.5 4
{SecStructureView2} generalRibbonWidth setValue 2
{SecStructureView2} options setValue 0
{SecStructureView2} backboneTubeRadius setMinMax 0.100000001490116 0.5
{SecStructureView2} backboneTubeRadius setValue 0.2
{SecStructureView2} colorschemeBB setIndex -1
{SecStructureView2} colorschemeBB untouch
{SecStructureView2} colorschemeBB setOptValue 0 0
{SecStructureView2} colorschemeBB setOptValue 1 0
{SecStructureView2} helixShape setValue 1
{SecStructureView2} helixTubeRadius setMinMax 0.100000001490116 2
{SecStructureView2} helixTubeRadius setValue 0.5
{SecStructureView2} helixCylinderRadius setMinMax 0.100000001490116 4
{SecStructureView2} helixCylinderRadius setValue 2.1
{SecStructureView2} helixRibbonWidth setMinMax 0.5 2
{SecStructureView2} helixRibbonWidth setValue 1
{SecStructureView2} colorschemeH setIndex -1
{SecStructureView2} colorschemeH untouch
{SecStructureView2} colorschemeH setOptValue 0 0
{SecStructureView2} colorschemeH setOptValue 1 0
{SecStructureView2} sheetShape setValue 1
{SecStructureView2} sheetArrowWidth setMinMax 0.5 5
{SecStructureView2} sheetArrowWidth setValue 1.5
{SecStructureView2} sheetArrowOptions setValue 0 1
{SecStructureView2} sheetArrowOptions setValue 1 1
{SecStructureView2} sheetArrowOptions setValue 2 1
{SecStructureView2} sheetRadius setMinMax 0.100000001490116 2
{SecStructureView2} sheetRadius setValue 0.3
{SecStructureView2} colorschemeS setIndex -1
{SecStructureView2} colorschemeS untouch
{SecStructureView2} colorschemeS setOptValue 0 0
{SecStructureView2} colorschemeS setOptValue 1 0
{SecStructureView2} turnTubeRadius setMinMax 0.100000001490116 2
{SecStructureView2} turnTubeRadius setValue 0.3
{SecStructureView2} colorschemeT setIndex -1
{SecStructureView2} colorschemeT untouch
{SecStructureView2} colorschemeT setOptValue 0 0
{SecStructureView2} colorschemeT setOptValue 1 0
{SecStructureView2} structures setValue 0 1
{SecStructureView2} structures setValue 1 0
{SecStructureView2} structures setValue 2 0
{SecStructureView2} structures setValue 3 0
{SecStructureView2} complexity setMinMax 0 1
{SecStructureView2} complexity setValue 0.5
{SecStructureView2} buffer setIndex -1
{SecStructureView2} buffer untouch
{SecStructureView2} fire
{SecStructureView2} discreteColormapBB setLocalMinMax 0.000000 21.000000
{SecStructureView2} continuousColormapBB setLocalMinMax 0.000000 21.000000
{SecStructureView2} discreteColormapH setLocalMinMax 0.000000 21.000000
{SecStructureView2} continuousColormapH setLocalMinMax 0.000000 21.000000
{SecStructureView2} discreteColormapS setLocalMinMax 0.000000 21.000000
{SecStructureView2} continuousColormapS setLocalMinMax 0.000000 21.000000
{SecStructureView2} discreteColormapT setLocalMinMax 0.000000 21.000000
{SecStructureView2} continuousColormapT setLocalMinMax 0.000000 21.000000
SecStructureView2 fire
SecStructureView2 setViewerMask 16383
SecStructureView2 select

set hideNewModules 0
create HxSecStructure {SecStructureView3}
SecStructureView3 setIconPosition 258 214
SecStructureView3 data connect 2JEL.pdb
{SecStructureView3} discreteColormapBB setDefaultColor 0.78 0.78 0.78
{SecStructureView3} discreteColormapBB setDefaultAlpha 1.000000
{SecStructureView3} discreteColormapBB setLocalRange 1
{SecStructureView3} discreteColormapBB setLocalMinMax 0.000000 21.000000
{SecStructureView3} continuousColormapBB setDefaultColor 0.898039 0.2 0.2
{SecStructureView3} continuousColormapBB setDefaultAlpha 1.000000
{SecStructureView3} continuousColormapBB setLocalRange 1
{SecStructureView3} continuousColormapBB setLocalMinMax 0.000000 21.000000
{SecStructureView3} discreteColormapH setDefaultColor 0.3 0.3 0.9
{SecStructureView3} discreteColormapH setDefaultAlpha 1.000000
{SecStructureView3} discreteColormapH setLocalRange 1
{SecStructureView3} discreteColormapH setLocalMinMax 0.000000 21.000000
{SecStructureView3} continuousColormapH setDefaultColor 0.898039 0.2 0.2
{SecStructureView3} continuousColormapH setDefaultAlpha 1.000000
{SecStructureView3} continuousColormapH setLocalRange 1
{SecStructureView3} continuousColormapH setLocalMinMax 0.000000 21.000000
{SecStructureView3} discreteColormapS setDefaultColor 0.9 0.2 0.2
{SecStructureView3} discreteColormapS setDefaultAlpha 1.000000
{SecStructureView3} discreteColormapS setLocalRange 1
{SecStructureView3} discreteColormapS setLocalMinMax 0.000000 21.000000
{SecStructureView3} continuousColormapS setDefaultColor 0.9 0.2 0.2
{SecStructureView3} continuousColormapS setDefaultAlpha 1.000000
{SecStructureView3} continuousColormapS setLocalRange 1
{SecStructureView3} continuousColormapS setLocalMinMax 0.000000 21.000000
{SecStructureView3} discreteColormapT setDefaultColor 0.4 0.4 0.4
{SecStructureView3} discreteColormapT setDefaultAlpha 1.000000
{SecStructureView3} discreteColormapT setLocalRange 1
{SecStructureView3} discreteColormapT setLocalMinMax 0.000000 21.000000
{SecStructureView3} continuousColormapT setDefaultColor 0.4 0.4 0.4
{SecStructureView3} continuousColormapT setDefaultAlpha 1.000000
{SecStructureView3} continuousColormapT setLocalRange 1
{SecStructureView3} continuousColormapT setLocalMinMax 0.000000 21.000000
{SecStructureView3} fire
{SecStructureView3} selectAtoms zab HIJMGDGABIAFIDBFPMPPPPPPNPHPBKABAAKHNJFLKE
{SecStructureView3} generalShape setValue 0
{SecStructureView3} generalThreadsWidth setMinMax 0.5 4
{SecStructureView3} generalThreadsWidth setValue 2
{SecStructureView3} generalRibbonWidth setMinMax 0.5 4
{SecStructureView3} generalRibbonWidth setValue 2
{SecStructureView3} options setValue 0
{SecStructureView3} backboneTubeRadius setMinMax 0.100000001490116 0.5
{SecStructureView3} backboneTubeRadius setValue 0.2
{SecStructureView3} colorschemeBB setIndex -1
{SecStructureView3} colorschemeBB untouch
{SecStructureView3} colorschemeBB setOptValue 0 0
{SecStructureView3} colorschemeBB setOptValue 1 0
{SecStructureView3} helixShape setValue 1
{SecStructureView3} helixTubeRadius setMinMax 0.100000001490116 2
{SecStructureView3} helixTubeRadius setValue 0.5
{SecStructureView3} helixCylinderRadius setMinMax 0.100000001490116 4
{SecStructureView3} helixCylinderRadius setValue 2.1
{SecStructureView3} helixRibbonWidth setMinMax 0.5 2
{SecStructureView3} helixRibbonWidth setValue 1
{SecStructureView3} colorschemeH setIndex -1
{SecStructureView3} colorschemeH untouch
{SecStructureView3} colorschemeH setOptValue 0 0
{SecStructureView3} colorschemeH setOptValue 1 0
{SecStructureView3} sheetShape setValue 1
{SecStructureView3} sheetArrowWidth setMinMax 0.5 5
{SecStructureView3} sheetArrowWidth setValue 1.5
{SecStructureView3} sheetArrowOptions setValue 0 1
{SecStructureView3} sheetArrowOptions setValue 1 1
{SecStructureView3} sheetArrowOptions setValue 2 1
{SecStructureView3} sheetRadius setMinMax 0.100000001490116 2
{SecStructureView3} sheetRadius setValue 0.3
{SecStructureView3} colorschemeS setIndex -1
{SecStructureView3} colorschemeS untouch
{SecStructureView3} colorschemeS setOptValue 0 0
{SecStructureView3} colorschemeS setOptValue 1 0
{SecStructureView3} turnTubeRadius setMinMax 0.100000001490116 2
{SecStructureView3} turnTubeRadius setValue 0.3
{SecStructureView3} colorschemeT setIndex -1
{SecStructureView3} colorschemeT untouch
{SecStructureView3} colorschemeT setOptValue 0 0
{SecStructureView3} colorschemeT setOptValue 1 0
{SecStructureView3} structures setValue 0 1
{SecStructureView3} structures setValue 1 1
{SecStructureView3} structures setValue 2 1
{SecStructureView3} structures setValue 3 0
{SecStructureView3} complexity setMinMax 0 1
{SecStructureView3} complexity setValue 0.5
{SecStructureView3} buffer setIndex -1
{SecStructureView3} buffer untouch
{SecStructureView3} fire
{SecStructureView3} discreteColormapBB setLocalMinMax 0.000000 21.000000
{SecStructureView3} continuousColormapBB setLocalMinMax 0.000000 21.000000
{SecStructureView3} discreteColormapH setLocalMinMax 0.000000 21.000000
{SecStructureView3} continuousColormapH setLocalMinMax 0.000000 21.000000
{SecStructureView3} discreteColormapS setLocalMinMax 0.000000 21.000000
{SecStructureView3} continuousColormapS setLocalMinMax 0.000000 21.000000
{SecStructureView3} discreteColormapT setLocalMinMax 0.000000 21.000000
{SecStructureView3} continuousColormapT setLocalMinMax 0.000000 21.000000
SecStructureView3 fire
SecStructureView3 setViewerMask 16383

set hideNewModules 0
create HxMolView {MoleculeView3}
MoleculeView3 setIconPosition 279 244
MoleculeView3 data connect 2JEL.pdb
{MoleculeView3} continuousColormap setDefaultColor 0 0 1
{MoleculeView3} continuousColormap setDefaultAlpha 1.000000
{MoleculeView3} discreteColormap setDefaultColor 0 0 1
{MoleculeView3} discreteColormap setDefaultAlpha 1.000000
{MoleculeView3} fire
{MoleculeView3} selectAtoms zab HIJMGDGABIAFIDBFPMPPPPPPNPHPCKACKAJBIMDALDABFKDAEPLB
{MoleculeView3} mode setValue 0
{MoleculeView3} quality setValue 1
{MoleculeView3} options setValue 0 0
{MoleculeView3} options setValue 1 0
{MoleculeView3} options setValue 2 0
{MoleculeView3} atomRadius setMinMax 0 2
{MoleculeView3} atomRadius setValue 1
{MoleculeView3} bondRadius setMinMax 0 0.5
{MoleculeView3} bondRadius setValue 0.05
{MoleculeView3} lineWidth setMinMax 1 3
{MoleculeView3} lineWidth setValue 2
{MoleculeView3} complexity setMinMax 0 1
{MoleculeView3} complexity setValue 0.2
{MoleculeView3} twistFactor setMinMax 0.5 2
{MoleculeView3} twistFactor setValue 1
{MoleculeView3} colorscheme setOptValue 0 0
{MoleculeView3} colorscheme setOptValue 1 0
{MoleculeView3} buffer setIndex -1
{MoleculeView3} buffer untouch
MoleculeView3 fire
MoleculeView3 setViewerMask 16382

set hideNewModules 0


viewer 0 setCameraPosition 62.3494 2.09092 -102.364
viewer 0 setCameraOrientation -0.96301 -0.185098 -0.195834 3.439
viewer 0 setCameraFocalDistance 154.73
viewer 0 setAutoRedraw 1
viewer 0 redraw
