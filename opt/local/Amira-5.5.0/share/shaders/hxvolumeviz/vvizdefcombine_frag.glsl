VVIZ_DATATYPE VVizGetData(vec2 tcoord);
VVIZ_DATATYPE VVizGetData(vec3 tcoord);

VVIZ_DATATYPE VVizCombineData(vec3 tcoord)
{
  return VVizGetData(tcoord);
}

VVIZ_DATATYPE VVizCombineData(vec2 tcoord)
{
  return VVizGetData(tcoord);
}
