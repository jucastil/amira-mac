
# see if the expression contains only valid pairs of attributes and values
# returns {} on success, an error string otherwise
proc check_attribute_values_validity expression_attributes {
  foreach expression $expression_attributes {
    set attribute [lindex $expression  1]
    set value [lindex $expression  2]
    set operator [lindex $expression  5]
    
    if {![attribute_exists $attribute]} {
      return "Attribute $attribute doesn't exist. Available Attributes are\n[get_all_attributes]"
    }
    if {![attribute_value_allowed $attribute $value]} {
      return "$value is not a valid value for attribute '$attribute'. Valid values are (the \" are necessary)\n[get_all_values $attribute]"
    }
    if {$value == "all" && $operator=="!=" } {
      return "value all is not allowed with operator !=."
    }
  }
  return {}
}



# see if the file attributes contain only valid pairs of attributes and values
# returns {} on success, an error string otherwise
proc check_description_attribute_values_validity read_attributes {
  foreach expression $read_attributes {
    set attribute [lindex $expression  0]
    set values [lindex $expression  1]
    
    foreach value $values {
      
      if {$value == "all"} {
        return "value all is not allowed as value for any attribute."
      }
      if {![attribute_exists $attribute]} {
        return "Attribute $attribute doesn't exist. Available Attributes are\n[get_all_attributes]"
      }
      if {![attribute_value_allowed $attribute $value]} {
        return "$value is not a valid value for attribute '$attribute'. Valid values are\n[get_all_values $attribute 1]"
      }
    }
  }
  return {}
}

# returns those attributes with default values that do not occur in the expression_attributes 
proc get_not_occuring_attributes_with_default_value expression_attributes {
  global attributes_default_values
  
  set ret [list]
  
  set attributes [array names attributes_default_values]
  
  foreach attribute $attributes {
    set attribute_occurs 0
    
    set default $attributes_default_values($attribute)
    
    if {$default !={} && $default != {any} } { 
      foreach expression $expression_attributes {
      
        set expr_attribute [lindex $expression  1]
        if {$expr_attribute == $attribute} {
          set attribute_occurs 1
          break
        }
      }
      
      if {!$attribute_occurs} {
        lappend ret $attribute
      }
      
    }
  }
  return $ret
}

# returns 1 if the attribute given in $attribute exists, 0 otherwise
proc attribute_exists attribute {
  global attributes_values
  return [expr [lsearch [array names attributes_values] $attribute]!=-1]
}


# returns a string with all valid attributes, one attribute per line
proc get_all_attributes {} {
  global attributes_values
  set attributes [array names attributes_values]
  return [join $attributes "\n"]
}

# returns a string with all valid attributes, one attribute per line
proc get_all_attributes_and_values {} {
  global attributes_values
  set ret {}
  set attributes [array names attributes_values]
  foreach attribute $attributes {
    set ret "$ret\n$attribute => [join $attributes_values($attribute) ","]"
  }
  return $ret
}

# returns 1, if the (existing!) attribute $attribute allows the value $value, 0 otherwise
proc attribute_value_allowed {attribute value} {
  global attributes_values
  return [expr [lsearch $attributes_values($attribute) $value] != -1]
}

# returns a string with all valid values of (valid!) attribute $attribute
proc get_all_values {attribute {for_xml_file 0}} {
  global attributes_values
  if {$for_xml_file==1} {
    set ret [list]
    foreach value $attributes_values($attribute) {
      if {$value!="any"} {
        regsub -all {"} $value ""  value
        lappend ret $value
      }
    }
      return [join $ret "\n"]
  } else {
    return [join $attributes_values($attribute) "\n"]
  }
}

# removes all occurences of "all" from expression
# attribute==all is replaced by 1
# cause its always true
proc replace_tautological_expressions { expression_string expression_attributes } {
  set adjust_index 0
  foreach expression $expression_attributes {
    set match [lindex $expression  0]
    set value [lindex $expression  2]
    set first_index [lindex $expression  3]
    set last_index [lindex $expression  4]
    
    if {$value=="any"} {
      set expression_string [string replace $expression_string [expr $first_index - $adjust_index] [expr $last_index - $adjust_index] "1"]
      
      set adjust_index [expr $adjust_index + [string length $match] - 1]
    }
    
    
  }
  return $expression_string
}

proc add_default_attributes {expression default_attributes} {
  global attributes_default_values
  set add_expr {}
  foreach default_attribute $default_attributes {
    set default_value $attributes_default_values($default_attribute)
    set add_expr "${add_expr}$default_attribute == $default_value && "
  }
  if {$add_expr!={} } {
    set add_expr "${add_expr}($expression)"
  }
}

# returns a list of attribute-value-expressions that occur in $expression
# attribute-value-expressions are of type 
# attribute == value
# attribute != value
# the returned list has entries of type list that contain the following information
# 0: the full match
# 1: the attribute (left of ==, !=)
# 2: the value (right of ==, !=)
# 3: start index of match within $expression
# 4: end idx of match $expression
# 5: the operator != or ==
proc get_expression_attributes {expression} {
  set expression_attributes [list]
  
  
  #set regexp {([a-zA-Z]+)\s*([!=]=)\s*("[a-zA-Z0-9\-]*"|any)} XXX
  set regexp {([a-zA-Z]+)\s*([!=]=)\s*([a-zA-Z0-9\-]*)}
  
  set index 0
  while {[regexp -start $index $regexp $expression match attr operator value]} {
    
    # get matching idxes of 
    regexp -start $index -indices $regexp $expression match2 attridx operatoridx valueidx
    set startidx [lindex $attridx 0]
    set endidx [lindex $valueidx 1]
    
    # update regexp index
    set index [expr $endidx + 1]
    
    
    # set a result list: 
    # 0: the full match
    # 1: the attribute (left of ==, !=)
    # 2: the value (right of ==, !=)
    # 3: start index of match
    # 4: end idx of match
    # 5: the operator != or ==
    set this_match [list $match $attr $value $startidx $endidx $operator]
    
    lappend expression_attributes $this_match
    
  }
  return $expression_attributes
}  

proc read_available_attributes {} {
  global AMIRA_ROOT
  global attributes_values
  global attributes_default_values
  
  set XSL [open "|xsltproc \"$AMIRA_ROOT/share/hxdemos-scripts/getAttributes.xsl\" \"$AMIRA_ROOT/share/hxdemos-scripts/attributes.xml\""]
  
  while {![eof $XSL]} {
    gets $XSL attribute_string
    
    if {$attribute_string eq ""} {
      break
    }
    
    set attribute_list [split $attribute_string "|"]
    
    set attribute [lindex $attribute_list 0]
    set select_any [lindex $attribute_list 1]
    set default_val [lindex $attribute_list 2]
    set values [split [lindex $attribute_list 3] ","]
    
    set all_values [list]
    
    if {$select_any == "yes"} {
      lappend all_values {any}
    }
    foreach value $values {
      lappend all_values "$value"
    }
    
    set attributes_values($attribute) $all_values
    if {$default_val!={any}} {
      set default_val "$default_val"
    }
    set attributes_default_values($attribute) $default_val   
  }
}

# returns a list of the attributes in $file
# each element of the list is a list
# 0: name of attribute
# 1: list of all values
proc read_description_attributes {filename} {
  global AMIRA_ROOT
  global file_attribute_values
  
  set ret [list]
  
  set XSL [open "|xsltproc \"$AMIRA_ROOT/share/hxdemos-scripts/getDescriptionAttributes.xsl\" \"$filename\""]
  array unset file_attribute_values
  
  while {![eof $XSL]} {
    gets $XSL attribute_string
    
    
    regsub {^\s*} $attribute_string "" attribute_string
    regsub {\s*$} $attribute_string "" attribute_string
    
    if {$attribute_string != ""} {
      set attribute_list [split $attribute_string "|"]
      
      set attribute [lindex $attribute_list 0]
      set values [split [lindex $attribute_list 1] ","]
      
      #~ for {set i 0 } { $i < [llength $values] } { incr i} {
        #~ set values [lreplace $values $i $i "\"[lindex $values $i]\""]
      #~ }
      
      lappend ret [list $attribute $values] 
      
      set file_attribute_values($attribute) $values
    }
  }
  return $ret
}

# Replaces all attribute-value pairs 
# attribute == "value"
#  by [expr [lsearch $file_attribute_values($attribute) {"value"}] != -1]
# attribute != "value"
#  by [expr [lsearch $file_attribute_values($attribute) {"value"}] == -1]
proc get_lsearch_expression { expression_string expression_attributes } {
  set adjust_index 0
  foreach expression $expression_attributes {
    set match [lindex $expression  0]
    set attribute [lindex $expression  1]
    set value [lindex $expression  2]
    set first_index [lindex $expression  3]
    set last_index [lindex $expression  4]
    set operator [lindex $expression  5]
    
    if {$operator=="=="} {
      set replacement "\[expr \[lsearch \$file_attribute_values($attribute) {$value}\] != -1\]"
    } else {
      set replacement "\[expr \[lsearch \$file_attribute_values($attribute) {$value}\] == -1\]"
    }
    
    set expression_string [string replace $expression_string [expr $first_index + $adjust_index] [expr $last_index + $adjust_index] $replacement]
      
    set adjust_index [expr $adjust_index +  [string length $replacement] - [string length $match] ]
    
  }
  return $expression_string
}


# get the expression that has to be evaluated to find out, if a
# given description file has to be considered or not based on 
# attributes
# read_available_attributes must be called prior to calling attribute_expression
proc attribute_expression {expression} {

  # read attributes from setup/description.xml
  # read_available_attributes

  # compile the expression: find attribute-value pairs
  set expression_attributes  [get_expression_attributes $expression]
  
  # check if all attribute-value-pairs are valid
  set validity [check_attribute_values_validity $expression_attributes]
  if {$validity != {}} {
    puts $validity
    exit
  }
  
  # check, which attributes with default values do not occur in the expression 
  # those have to be added later with their default value
  set attributes_with_default_value_not_occuring [get_not_occuring_attributes_with_default_value $expression_attributes]
  
  # expressions with attribute == all are tautological. replace them by 1 (always true)
  set expression [ replace_tautological_expressions $expression $expression_attributes ]
  #puts $expression
  
  # add the necessary default expressions
  set expression [ add_default_attributes $expression $attributes_with_default_value_not_occuring ]
  
  
  # the expression is now ready to go
  if {[llength $attributes_with_default_value_not_occuring] > 0} {
    if {[llength $attributes_with_default_value_not_occuring] ==1 } {
      set Attributes {Attribute}
      set have {has}
      set their {its}
      set values {value}
    } else {
      set Attributes {Attribute}
      set have {have}
      set values {values}
    }
    puts "$Attributes '[join $attributes_with_default_value_not_occuring ", "]' $have been added to expression with $their default $values. Expression is now\n$expression"
  }
  
  
  # the expression is now ready to go. Now all attribute-value pairs 
  # attribute == "value"
  # has to be replaced by [expr [lsearch $file_attribute_values($attribute) {"value"}] != -1]
  # attribute != "value"
  # has to be replaced by [expr [lsearch $file_attribute_values($attribute) {"value"}] == -1]
  
  # to this end, the expression must be compiled again
  set expression_attributes  [get_expression_attributes $expression]
  
  set lsearch_expression [get_lsearch_expression $expression $expression_attributes]
  #~ puts $lsearch_expression
  
  #~ puts $file_attribute_values(state)
  
  # create list to store the names of all used attributes
  set used_attributes [list]
  
  foreach expression $expression_attributes {
    # append used attribute name to list
    lappend used_attributes [lindex $expression 1]
  }
  
  return [list $used_attributes $lsearch_expression]
}


# read attributes from file and evaluate the expression to see, if its valid
proc file_fulfills_attributes {attribute_expression used_attributes description_xml} {
  
  # if no attributes_expression has been passed, return 1
  
  if { $attribute_expression == {}} {
    return 1;
  }
  
  # read the attributes from the description file
  set read_attributes [ read_description_attributes $description_xml]
  
  # determine list of attribute names from $read_attributes
  set given_attributes [list]
  foreach read_attribute $read_attributes {
    lappend given_attributes [lindex $read_attribute 0]
  }
  
  # go through all attribute names used in expression
  foreach used_attribute $used_attributes {
    # if an attribute that is used in the expression is not set in description.xml
    # this file has to be skipped
    if {[lsearch $given_attributes $used_attribute] == -1} {
      return 0
    }
  }
  
  
  set validity [check_description_attribute_values_validity $read_attributes]
  if {$validity != {}} {
    puts "In input file $description_xml:\n$validity"
    exit
  }
  
  #~ global file_attribute_values
  #~ foreach attribute [array names file_attribute_values] {
  #~   puts "$attribute => [ lindex $file_attribute_values($attribute) 0]"
  #~ }
  #~ exit
  global file_attribute_values
  return [expr $attribute_expression]

}







proc test_attributes input_expression {

  # get the expression from command line
  #~ set input_expression [lindex $argv 0]
  
  set used_attr_attr_expr [attribute_expression $input_expression]
  
  set used_attributes [lindex $used_attr_attr_expr 0]
  set attribute_expression [lindex $used_attr_attr_expr 1]
  
  # process description file
  set description_xml [lindex $argv 1]
  
  return [file_fulfills_attributes $attribute_expression $used_attributes $description_xml]
}
