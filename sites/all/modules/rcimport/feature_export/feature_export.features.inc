<?php
/**
 * @file
 * feature_export.features.inc
 */

/**
 * Implements hook_node_info().
 */
function feature_export_node_info() {
  $items = array(
    'export' => array(
      'name' => t('Export'),
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
