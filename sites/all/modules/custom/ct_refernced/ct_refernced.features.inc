<?php
/**
 * @file
 * ct_refernced.features.inc
 */

/**
 * Implements hook_node_info().
 */
function ct_refernced_node_info() {
  $items = array(
    'ct_referenced' => array(
      'name' => t('CT referenced'),
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
