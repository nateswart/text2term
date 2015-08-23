# Text2Term

This is a simple drush extension to aid in the conversion of a text field to a taxonomy field. To be safe, it does not create the new vocabulary nor does it remove the existing text field the data originated from. That is left up to the sitebuilder to manager.

## Basic steps

1. Create a new vocabulary to hold the taxonomy values.
2. Add a new taxonomy field to the content type with the original text field.
2. Run `drush t2t <node_type> <textfield> <termfield> <vocabulary>`
4. Validate everything looks good.
5. Delete the text field (if you want) from your content type.

Example: 
`drush t2t article field_text_tag field_new_tag new_vocabulary`
