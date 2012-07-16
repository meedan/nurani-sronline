<?php

/**
 * Implementation of hook_ckeditor_profile_defaults().
 */
function sronline_general_ckeditor_profile_defaults() {
  $data = array(
    'CKEditor Global Profile' => array(
      'name' => 'CKEditor Global Profile',
      'settings' => array(
        'rank' => array(
          '0' => '3',
        ),
        'excl_mode' => '1',
        'excl' => 'node/add*
node/*/edit',
        'simple_incl' => '*.edit-signature
admin/settings/site-information.*
admin/settings/site-maintenance.*
*.edit-page-help
*.edit-user-registration-help
*.edit-user-picture-guidelines
news_articles@*.edit-body
basic_page@*.edit-body
video@*.edit-body
news_articles@*.edit-body
',
        'simple_toolbar' => '[
    [\'Format\',\'Bold\',\'Italic\',\'-\',\'NumberedList\',\'BulletedList\',\'Superscript\',\'-\',\'Cut\',\'Copy\',\'Paste\',\'Undo\',\'Redo\',\'Scayt\',\'-\',\'Anchor\',\'Link\',\'Unlink\']
]',
        'ckeditor_path' => '%b/sites/all/libraries/ckeditor',
        'ckeditor_local_path' => '',
        'ckeditor_plugins_path' => '%m/plugins',
        'ckeditor_plugins_local_path' => '',
        'ckfinder_path' => '%m/ckfinder',
        'show_fieldnamehint' => 't',
        'toolbar_wizard' => 't',
        'loadPlugins' => array(),
        'excl_regex' => '#(?:^.*:.*@node/add.*\\..*$)|(?:^.*:.*@node/.*/edit\\..*$)#',
        'simple_incl_regex' => '#(?:^.*:.*@.*\\.edit\\-signature$)|(?:^.*:.*@admin/settings/site\\-information\\..*$)|(?:^.*:.*@admin/settings/site\\-maintenance\\..*$)|(?:^.*:.*@.*\\.edit\\-page\\-help$)|(?:^.*:.*@.*\\.edit\\-user\\-registration\\-help$)|(?:^.*:.*@.*\\.edit\\-user\\-picture\\-guidelines$)|(?:^.*:news_articles@.*\\.edit\\-body$)|(?:^.*:basic_page@.*\\.edit\\-body$)|(?:^.*:video@.*\\.edit\\-body$)|(?:^.*:news_articles@.*\\.edit\\-body$)#',
      ),
      'roles' => array(),
    ),
  );
  return $data;
}
