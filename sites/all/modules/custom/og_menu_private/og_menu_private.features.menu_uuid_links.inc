<?php
/**
 * @file
 * og_menu_private.features.menu_uuid_links.inc
 */

/**
 * Implements hook_menu_default_menu_uuid_links().
 */
function og_menu_private_menu_default_menu_uuid_links() {
  $menu_uuid_links = array();

  // Exported menu link: 1d45e7ad-0be2-4ff9-8b89-9341b99aa75c
  $menu_uuid_links['1d45e7ad-0be2-4ff9-8b89-9341b99aa75c'] = array(
    'menu_name' => 'menu-og-369',
    'router_path' => 'node/%',
    'link_title' => 'Sub Private 1_1',
    'options' => array(),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'uuid' => '1d45e7ad-0be2-4ff9-8b89-9341b99aa75c',
    'parent_uuid' => '99c1c641-3dcf-4650-b17e-2eb297d6665e',
    'uuid_path' => 'node/dd2cae26-8944-496e-b058-dd2ddfa87f47',
  );
  // Exported menu link: 99c1c641-3dcf-4650-b17e-2eb297d6665e
  $menu_uuid_links['99c1c641-3dcf-4650-b17e-2eb297d6665e'] = array(
    'menu_name' => 'menu-og-369',
    'router_path' => 'node/%',
    'link_title' => 'Sub Private 1',
    'options' => array(),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'uuid' => '99c1c641-3dcf-4650-b17e-2eb297d6665e',
    'uuid_path' => 'node/f81564f6-d16f-4317-a414-ccf9a6165d7f',
  );
  // Exported menu link: d8a590f7-7c85-11e4-877f-080027d53c2e
  $menu_uuid_links['d8a590f7-7c85-11e4-877f-080027d53c2e'] = array(
    'menu_name' => 'menu-og-369',
    'router_path' => 'node/%',
    'link_title' => 'Sub Private 2',
    'options' => array(),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'uuid' => 'd8a590f7-7c85-11e4-877f-080027d53c2e',
    'uuid_path' => 'node/f4202729-2d89-4c96-8dac-0d2f55539b2b',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Sub Private 1');
  t('Sub Private 1_1');
  t('Sub Private 2');


  return $menu_uuid_links;
}
