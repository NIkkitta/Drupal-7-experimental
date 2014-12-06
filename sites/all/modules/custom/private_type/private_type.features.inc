<?php
/**
 * @file
 * private_type.features.inc
 */

/**
 * Implements hook_node_info().
 */
function private_type_node_info() {
  $items = array(
    'private' => array(
      'name' => t('Private'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
