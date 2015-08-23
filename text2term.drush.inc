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
  drush_print("Processing for '" . $type . "': Copying " . $textfield . " to " . $termfield . ".");

  // Select all notes of type $type

  // Loop through each node

    // Access the $textfield

    // Find the tid of the value in $vocabulary

    // If no tid is found, create the tid in $vocabulary

    // Set the tid on the node

}
