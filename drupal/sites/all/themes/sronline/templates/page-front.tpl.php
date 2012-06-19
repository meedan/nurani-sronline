<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">
  <head>
    
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>
    <?php print $styles; ?>
    <!--[if lte IE 6]><link type="text/css" rel="stylesheet" media="all" href="<?php print $base_path . path_to_theme(); ?>/css/ie6.css" /><![endif]-->
    <!--[if IE 7]><link type="text/css" rel="stylesheet" media="all" href="<?php print $base_path . path_to_theme(); ?>/css/ie7.css" /><![endif]-->
    <!--[if IE 8]><link type="text/css" rel="stylesheet" media="all" href="<?php print $base_path . path_to_theme(); ?>/css/ie8.css" /><![endif]-->
    <?php print $scripts; ?>
  </head>

  <body class="<?php print $body_classes; ?>">
    <div id="bg">
    	<img src="/meedan-sronline/drupal/sites/all/themes/sronline/images/bg.jpg" alt="">
    </div>
    <div id="skip">
      <a href="#content"><?php print t('Skip to Content'); ?></a>
      <?php if (!empty($primary_links) || !empty($secondary_links)): ?>
        <a href="#navigation"><?php print t('Skip to Navigation'); ?></a>
      <?php endif; ?>
    </div>
    
    <div class="wrapper">
    <!-- ______________________ HEADER _______________________ -->

    <div id="header">
        <?php if (!empty($logo)): ?>
          <a href="<?php print $front_page; ?>" class="logo" title="<?php print t('Home'); ?>" rel="home" id="logo">
            <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>"/>
          </a>
        <?php endif; ?>
        <div id="search_bar">
         <?php //print $header; ?>
         <?php // print $search_box; ?>
        </div>
    </div> <!-- /header -->
    
     <!-- ______________________ NAVIGATION _______________________ -->
     <?php if (!empty($navigation)): ?>
         <div><?php print $navigation; ?></div><!--/navigation-->
     <?php endif; ?>
     <?php if (!empty($content_top)): ?>
         <div id="banner_area"><?php print $content_top; ?></div<!--/navigation-->
     <?php endif; ?>
    
   
      <!-- ______________________ FOOTER _______________________ -->

      <?php if(!empty($footer_message) || !empty($footer_block)): ?>
        <div id="footer">
          <?php print $footer_message; ?>
          <?php print $footer_block; ?>
        </div> <!-- /footer -->
      <?php endif; ?>

    </div> <!-- /page -->
    <?php print $closure; ?>
  </body>
</html>
