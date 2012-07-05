<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function sronline_general_user_default_permissions() {
  $permissions = array();

  // Exported permission: access administration menu
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: access administration pages
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: access all webform results
  $permissions['access all webform results'] = array(
    'name' => 'access all webform results',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: access ckeditor
  $permissions['access ckeditor'] = array(
    'name' => 'access ckeditor',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: access comments
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
      '3' => 'editor',
    ),
  );

  // Exported permission: access content
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: access own webform results
  $permissions['access own webform results'] = array(
    'name' => 'access own webform results',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: access own webform submissions
  $permissions['access own webform submissions'] = array(
    'name' => 'access own webform submissions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: access site reports
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: administer comments
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: administer permissions
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer users
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: create basic_page content
  $permissions['create basic_page content'] = array(
    'name' => 'create basic_page content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: create home_banner content
  $permissions['create home_banner content'] = array(
    'name' => 'create home_banner content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: create news_articles content
  $permissions['create news_articles content'] = array(
    'name' => 'create news_articles content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: create testimonial content
  $permissions['create testimonial content'] = array(
    'name' => 'create testimonial content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: create text_bundle content
  $permissions['create text_bundle content'] = array(
    'name' => 'create text_bundle content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: create url aliases
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: create video content
  $permissions['create video content'] = array(
    'name' => 'create video content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: create webform content
  $permissions['create webform content'] = array(
    'name' => 'create webform content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete all webform submissions
  $permissions['delete all webform submissions'] = array(
    'name' => 'delete all webform submissions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete any basic_page content
  $permissions['delete any basic_page content'] = array(
    'name' => 'delete any basic_page content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete any home_banner content
  $permissions['delete any home_banner content'] = array(
    'name' => 'delete any home_banner content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete any news_articles content
  $permissions['delete any news_articles content'] = array(
    'name' => 'delete any news_articles content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete any testimonial content
  $permissions['delete any testimonial content'] = array(
    'name' => 'delete any testimonial content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete any text_bundle content
  $permissions['delete any text_bundle content'] = array(
    'name' => 'delete any text_bundle content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete any video content
  $permissions['delete any video content'] = array(
    'name' => 'delete any video content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete any webform content
  $permissions['delete any webform content'] = array(
    'name' => 'delete any webform content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete own basic_page content
  $permissions['delete own basic_page content'] = array(
    'name' => 'delete own basic_page content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete own home_banner content
  $permissions['delete own home_banner content'] = array(
    'name' => 'delete own home_banner content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete own news_articles content
  $permissions['delete own news_articles content'] = array(
    'name' => 'delete own news_articles content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete own testimonial content
  $permissions['delete own testimonial content'] = array(
    'name' => 'delete own testimonial content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete own text_bundle content
  $permissions['delete own text_bundle content'] = array(
    'name' => 'delete own text_bundle content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete own video content
  $permissions['delete own video content'] = array(
    'name' => 'delete own video content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete own webform content
  $permissions['delete own webform content'] = array(
    'name' => 'delete own webform content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete own webform submissions
  $permissions['delete own webform submissions'] = array(
    'name' => 'delete own webform submissions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: delete revisions
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit all webform submissions
  $permissions['edit all webform submissions'] = array(
    'name' => 'edit all webform submissions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit any basic_page content
  $permissions['edit any basic_page content'] = array(
    'name' => 'edit any basic_page content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit any home_banner content
  $permissions['edit any home_banner content'] = array(
    'name' => 'edit any home_banner content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit any news_articles content
  $permissions['edit any news_articles content'] = array(
    'name' => 'edit any news_articles content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit any testimonial content
  $permissions['edit any testimonial content'] = array(
    'name' => 'edit any testimonial content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit any text_bundle content
  $permissions['edit any text_bundle content'] = array(
    'name' => 'edit any text_bundle content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit any video content
  $permissions['edit any video content'] = array(
    'name' => 'edit any video content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit any webform content
  $permissions['edit any webform content'] = array(
    'name' => 'edit any webform content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit own basic_page content
  $permissions['edit own basic_page content'] = array(
    'name' => 'edit own basic_page content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit own home_banner content
  $permissions['edit own home_banner content'] = array(
    'name' => 'edit own home_banner content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit own news_articles content
  $permissions['edit own news_articles content'] = array(
    'name' => 'edit own news_articles content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit own testimonial content
  $permissions['edit own testimonial content'] = array(
    'name' => 'edit own testimonial content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit own text_bundle content
  $permissions['edit own text_bundle content'] = array(
    'name' => 'edit own text_bundle content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit own video content
  $permissions['edit own video content'] = array(
    'name' => 'edit own video content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit own webform content
  $permissions['edit own webform content'] = array(
    'name' => 'edit own webform content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: edit own webform submissions
  $permissions['edit own webform submissions'] = array(
    'name' => 'edit own webform submissions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: export nodes
  $permissions['export nodes'] = array(
    'name' => 'export nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: export own nodes
  $permissions['export own nodes'] = array(
    'name' => 'export own nodes',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: flush imagecache
  $permissions['flush imagecache'] = array(
    'name' => 'flush imagecache',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: post comments
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: post comments without approval
  $permissions['post comments without approval'] = array(
    'name' => 'post comments without approval',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: revert revisions
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  // Exported permission: search content
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache Home-image_613
  $permissions['view imagecache Home-image_613'] = array(
    'name' => 'view imagecache Home-image_613',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache Home-newsthumb-60
  $permissions['view imagecache Home-newsthumb-60'] = array(
    'name' => 'view imagecache Home-newsthumb-60',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache Home-video_294
  $permissions['view imagecache Home-video_294'] = array(
    'name' => 'view imagecache Home-video_294',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache Video_image_295
  $permissions['view imagecache Video_image_295'] = array(
    'name' => 'view imagecache Video_image_295',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache Video_image_556
  $permissions['view imagecache Video_image_556'] = array(
    'name' => 'view imagecache Video_image_556',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache about_us_560
  $permissions['view imagecache about_us_560'] = array(
    'name' => 'view imagecache about_us_560',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache news-image-104
  $permissions['view imagecache news-image-104'] = array(
    'name' => 'view imagecache news-image-104',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache news-image-294
  $permissions['view imagecache news-image-294'] = array(
    'name' => 'view imagecache news-image-294',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: view revisions
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'editor',
    ),
  );

  return $permissions;
}
