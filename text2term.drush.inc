<?php

/**
 * Implements hook_drush_command().
 */
function text2term_drush_command() {

  $items['text2term'] = array(
    'description' => 'Copy text values to taxonomy terms.',
    'aliases' => array('t2t'),
    'arguments' => array(
      'type' => 'The machine name of the content type to process.',
      'textfield' => 'The machine name of the textfield to use as input.',
      'termfield' => 'The machine name of the term field to store the taxonomy term.',
      'vocabulary' => 'The machine name of the vocabulary to store terms in.',
    ),
  );

  return $items;
}


/**
 * Callback for the text2term command
 */
function drush_text2term($type, $textfield, $termfield, $vocabulary) {
  drush_print("Processing " . $type . ": Copying " . $textfield . " to " . $termfield . ".");

  // Select all notes of type $type
  $query = "SELECT nid FROM {node} WHERE type=:type";
  $result = db_query($query, array(':type' => $type));

  // Loop through each node
  foreach ($result as $row) {
    $n = node_load($row->nid);
    $tf = field_get_items('node', $n, $textfield);

    // Find the tid of the value in $vocabulary
    if($tf[0]['value']) {
      $terms = taxonomy_get_term_by_name($tf[0]['value'], $vocabulary);
      drush_print(print_r($terms));

      // If no tid is found, create the tid in $vocabulary
      if(count($terms) == 0) {
        $vocab = taxonomy_vocabulary_machine_name_load($vocabulary);
        $term = new stdClass();
        $term->name = $tf[0]['value'];
        $term->vid = $vocab->vid;
        taxonomy_term_save($term);
        $tid = $term->tid;
      }
      else {
        $tid = array_shift($terms)->tid;
      }

      // Set the tid on the node
      if($newfield = $n->$termfield) {
        $newfield[$n->language][0]['tid'] = $tid;
      }
      else {
        $val = array($n->language);
        $val[$n->language] = array(array('tid' => $tid));
        $n->$termfield = $val;
      }
      $n->$termfield[$n->language][0]['tid'] = $tid;
      drush_print(print_r($n));
      node_save($n);
     }

  }
}
