<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">
<html>
 <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>
    <?php print $styles; ?>
    <!--[if lte IE 6]><link type="text/css" rel="stylesheet" media="all" href="<?php print $base_path . path_to_theme(); ?>/css/ie6.css" /><![endif]-->
    <!--[if IE 7]><link type="text/css" rel="stylesheet" media="all" href="<?php print $base_path . path_to_theme(); ?>/css/ie7.css" /><![endif]-->
    <!--[if IE 8]><link type="text/css" rel="stylesheet" media="all" href="<?php print $base_path . path_to_theme(); ?>/css/ie8.css" /><![endif]-->
    <?php print $scripts; ?>
  </head>
  <body>
  <div id="bg">
    <img src="images/bg.jpg" alt="">
  </div>
  <div class="wrapper">
    <div id="header"> <!--header-->
        <a class="logo" title="" href="/"> </a>
        <div id="search_bar">
          <input type="text" id="searchinput" name="searchinput" value= "Search Site..."/>
          <input type="image" id="submit_btn" name="submit_btn" value="Go" src="images/gobutton.png" />
        </div>
    </div> <!--header ends-->
   
  <ul id="nav" class="nav_main"><!--menu-->  
    <li><a href="/">Home</a></li>  
    <li class="list"><a href="#">About SR</a>
        <ul class="nav_sub">
            <li><a href="#">Introduction to SR</a></li>
            <li><a href="#">Guidelines & Rules</a></li>
            <li><a href="#">How to set up SR</a></li>
        </ul>
    </li>  
    <li><a href="#">Resources</a></li>  
    <li><a href="#">SR online</a></li>
    <li><a href="#">News & Events</a></li>  
    <li><a href="#">Contact Us</a></li>  
  </ul> <!--menu ends--> 
  
  <!-- top content-->
  <div id="banner_area">
    <ul>
      <li class="slides"> <a href="" ><img src="images/img_banner.jpg"/></a></li>
    </ul>
    <div id="video"></div>
    <div class="newsletter">
      <div class="title"></div>
      <input type="text" class="newsinput" name="newsinput" value= "Enter Email Adress..."/>
      <input type="submit" class="button" name="submit_btn" value="submit" />
    </div>
  </div>
  <!--top content ends>
  <!-- main_body-->
  <div id="bottom" class="home">
    <div class="box news">
      <div id="heading_1"> </div>
        <div class="content">
            <div class="item">
                <div class="icon"><img src="images/thumbnail.png" alt=""/></div>
                <div class="info">
                  <h2>Article Title</h2>
                  <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis varius pulvinar sem at fermentum. Ut scelerisque felis non leo sagittis elementum. Proin auctor feugiat </p>
                </div>
            </div>
          
        </div>
        <div class="content">
            <div class="item">
                <div class="icon"><img src="images/thumbnail.png" alt=""/></div>
                <div class="info">
                  <h2>Article Title</h2>
                  <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis varius pulvinar sem at fermentum. </p>
                </div>
            </div>
          
        </div>
        <div class="content">
            <div class="item">
                <div class="icon"><img src="images/thumbnail.png" alt=""/></div>
                <div class="info">
                  <h2>Article Title</h2>
                  <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p>
                </div>
            </div>
          
        </div>
         <div class="content">
            <div class="item">
                <div class="icon"><img src="images/thumbnail.png" alt=""/></div>
                <div class="info">
                  <h2>Article Title</h2>
                  <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p>
                </div>
            </div>
        </div>
      </div>
    <div class="box text">
     <div id="heading_2"> </div>
     <div class="content">
            <div class="item">
                <div class="icon pdf"><img src="images/pdf.gif" alt=""/></div>
                <div class="info">
                  <h2>Article Title</h2>
                  <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. consectetur adipiscing elit. Duis varius pulvinar sem at fermentum. Ut scelerisque felis non leo sagittis elementum.</p>
                </div>
            </div>
        </div>
         <div class="content">
            <div class="item">
                <div class="icon pdf"><img src="images/pdf.gif" alt=""/></div>
                <div class="info">
                  <h2>Article Title</h2>
                  <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p>
                </div>
            </div>
        </div>
         <div class="content">
            <div class="item">
                <div class="icon pdf"><img src="images/pdf.gif" alt=""/></div>
                <div class="info">
                  <h2>Article Title</h2>
                  <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. consectetur adipiscing elit. Duis varius pulvinar sem at fermentum. Ut scelerisque felis non leo sagittis elementum.</p>
                </div>
            </div>
        </div>
    </div>
    
    <div class="box testimonials">
     <div id="heading_3"> </div>
       <blockquote class="purpule">
          <span>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis varius pulvinar sem at fermentum. Ut scelerisque felis non leo sagittis elementum. Proin auctor feugiat sapien, vel scelerisque urna fringilla et. Maecenas ut. <cite> Zainab B.</cite> </span>
       </blockquote>
        <blockquote class="orange">
          <span>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis varius pulvinar sem at fermentum. Ut scelerisque felis non leo sagittis elementum. Proin auctor feugiat sapien, vel scelerisque urna fringilla et. Maecenas ut <cite> Zainab B.</cite> </span>
       </blockquote>

    </div>
  </div>
  <!-- main_body ends-->
  <div id="footer" class="home"> 
    <div id="footer_top"></div>
    <div id="bottom_footer">
        <p class="address"></p>
        <div class="secondary-menu"></div>
    
    </div>
  </div>
  </div>
</body>
</html>
