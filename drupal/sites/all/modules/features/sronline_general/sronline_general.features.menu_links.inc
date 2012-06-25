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
  // Exported menu link: primary-links:news
  $menu_links['primary-links:news'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'news',
    'router_path' => 'news',
    'link_title' => 'News',
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
  // Exported menu link: primary-links:node/11
  $menu_links['primary-links:node/11'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'node/11',
    'router_path' => 'node/%',
    'link_title' => 'Rules about SR',
    'options' => array(
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
    'parent_path' => 'node/2',
  );
  // Exported menu link: primary-links:node/12
  $menu_links['primary-links:node/12'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'node/12',
    'router_path' => 'node/%',
    'link_title' => 'More Sr Stuff',
    'options' => array(
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
    'parent_path' => 'node/2',
  );
  // Exported menu link: primary-links:node/13
  $menu_links['primary-links:node/13'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'node/13',
    'router_path' => 'node/%',
    'link_title' => 'How to do SR',
    'options' => array(
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '1',
    'weight' => '0',
    'parent_path' => 'node/2',
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
    'expanded' => '1',
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
    'expanded' => '1',
    'weight' => '-48',
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
    'weight' => '-44',
  );
  // Exported menu link: primary-links:text-bundles
  $menu_links['primary-links:text-bundles'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'text-bundles',
    'router_path' => 'text-bundles',
    'link_title' => 'Text Bundles',
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
  // Exported menu link: primary-links:videos
  $menu_links['primary-links:videos'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'videos',
    'router_path' => 'videos',
    'link_title' => 'Videos',
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
  t('How to do SR');
  t('More Sr Stuff');
  t('News');
  t('Privacy Policy');
  t('Resources');
  t('Rules about SR');
  t('Terms of Use');
  t('Text Bundles');
  t('Videos');


  return $menu_links;
}
