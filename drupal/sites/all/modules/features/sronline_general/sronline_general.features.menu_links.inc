<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function sronline_general_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:<front>
  $menu_links['primary-links:<front>'] = array(
    'menu_name' => 'primary-links',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: primary-links:node
  $menu_links['primary-links:node'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'node',
    'router_path' => 'node',
    'link_title' => 'News & Events',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-46',
  );
  // Exported menu link: primary-links:node/2
  $menu_links['primary-links:node/2'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'node/2',
    'router_path' => 'node/%',
    'link_title' => 'About SR',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '1',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: primary-links:node/3
  $menu_links['primary-links:node/3'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'node/3',
    'router_path' => 'node/%',
    'link_title' => 'Resources',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Exported menu link: primary-links:node/4
  $menu_links['primary-links:node/4'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'node/4',
    'router_path' => 'node/%',
    'link_title' => 'SR Online',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-47',
  );
  // Exported menu link: primary-links:node/5
  $menu_links['primary-links:node/5'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'node/5',
    'router_path' => 'node/%',
    'link_title' => 'Contact Us',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-45',
  );
  // Exported menu link: secondary-links:node/6
  $menu_links['secondary-links:node/6'] = array(
    'menu_name' => 'secondary-links',
    'link_path' => 'node/6',
    'router_path' => 'node/%',
    'link_title' => 'Terms of Use',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: secondary-links:node/7
  $menu_links['secondary-links:node/7'] = array(
    'menu_name' => 'secondary-links',
    'link_path' => 'node/7',
    'router_path' => 'node/%',
    'link_title' => 'Privacy Policy',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About SR');
  t('Contact Us');
  t('Home');
  t('News & Events');
  t('Privacy Policy');
  t('Resources');
  t('SR Online');
  t('Terms of Use');


  return $menu_links;
}
