<?php
/**
 * @file
 * og_menu_private.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function og_menu_private_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-og-369.
  $menus['menu-og-369'] = array(
    'menu_name' => 'menu-og-369',
    'title' => 'Private2',
    'description' => 'OG Menu for Private(n)',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('OG Menu for Private(n)');
  t('Private2');


  return $menus;
}
