<?php

/**
 * Implementation of hook_node_export_features_default().
 */
function sronline_general_node_export_features_default() {
  $node_export = array(
  'code_string' => 'array(
  array(
    \'nid\' => NULL,
    \'type\' => \'webform\',
    \'language\' => \'\',
    \'uid\' => \'1\',
    \'status\' => \'1\',
    \'created\' => NULL,
    \'changed\' => NULL,
    \'comment\' => \'0\',
    \'promote\' => \'1\',
    \'moderate\' => \'0\',
    \'sticky\' => \'0\',
    \'tnid\' => \'0\',
    \'translate\' => \'0\',
    \'vid\' => NULL,
    \'revision_uid\' => \'1\',
    \'title\' => \'Newsletter\',
    \'body\' => \'\',
    \'teaser\' => \'\',
    \'log\' => \'\',
    \'revision_timestamp\' => NULL,
    \'format\' => \'2\',
    \'name\' => \'admin\',
    \'picture\' => \'\',
    \'data\' => \'a:0:{}\',
    \'path\' => NULL,
    \'webform\' => array(
      \'nid\' => \'1\',
      \'confirmation\' => \'Thank you for signing up to the SR-Online newsletter.\',
      \'confirmation_format\' => \'2\',
      \'redirect_url\' => \'<none>\',
      \'status\' => \'1\',
      \'block\' => \'1\',
      \'teaser\' => \'0\',
      \'allow_draft\' => \'0\',
      \'auto_save\' => \'0\',
      \'submit_notice\' => \'0\',
      \'submit_text\' => \'\',
      \'submit_limit\' => \'-1\',
      \'submit_interval\' => \'-1\',
      \'total_submit_limit\' => \'-1\',
      \'total_submit_interval\' => \'-1\',
      \'record_exists\' => TRUE,
      \'roles\' => array(
        \'0\' => \'1\',
        \'1\' => \'2\',
      ),
      \'emails\' => array(),
      \'components\' => array(
        \'1\' => array(
          \'nid\' => \'1\',
          \'cid\' => \'1\',
          \'form_key\' => \'email_address\',
          \'name\' => \'Email Address\',
          \'type\' => \'email\',
          \'value\' => \'\',
          \'extra\' => array(
            \'title_display\' => \'before\',
            \'private\' => 0,
            \'disabled\' => 0,
            \'unique\' => 0,
            \'conditional_operator\' => \'=\',
            \'width\' => \'\',
            \'description\' => \'\',
            \'attributes\' => array(),
            \'conditional_component\' => \'\',
            \'conditional_values\' => \'\',
          ),
          \'mandatory\' => \'1\',
          \'pid\' => \'0\',
          \'weight\' => \'0\',
          \'page_num\' => 1,
        ),
      ),
    ),
    \'last_comment_timestamp\' => NULL,
    \'last_comment_name\' => NULL,
    \'comment_count\' => \'0\',
    \'taxonomy\' => array(),
    \'uuid\' => \'0fe9a33a-a037-11e1-8ac9-7e16f58cdaa2\',
    \'revision_uuid\' => \'ae4b19e0-cf59-11e1-be80-46e9befdb9a5\',
    \'menu\' => NULL,
    \'files\' => array(),
    \'#_export_node_encode_object\' => \'1\',
  ),
    array(
    \'nid\' => NULL,
    \'type\' => \'basic_page\',
    \'language\' => \'\',
    \'uid\' => \'1\',
    \'status\' => \'1\',
    \'created\' => NULL,
    \'changed\' => NULL,
    \'comment\' => \'0\',
    \'promote\' => \'0\',
    \'moderate\' => \'0\',
    \'sticky\' => \'0\',
    \'tnid\' => \'0\',
    \'translate\' => \'0\',
    \'vid\' => NULL,
    \'revision_uid\' => \'1\',
    \'title\' => \'About SR\',
    \'body\' => \'<p>&nbsp;</p>
<p>Lorem <strong>ipsum dolor</strong> sit amet, consectetur adipiscing elit. Nunc sagittis sodales vulputate. Integer porttitor, eros id iaculis mollis, <em>urna felis </em>consequat quam, id tincidunt dolor turpis vel sem. <a name="new ancor">Quisque quis</a> pharetra ipsum. Fusce tempor consequat facilisis. Morbi eros lorem, porta a porta varius, feugiat vel magna. Sed vulputate vestibulum cursus. Aliquam a vulputate mi. In rutrum eleifend felis, non tempor lorem vulputate a.</p>
<ul>
	<li>
		&nbsp;</li>
</ul>
<p>Nulla lacinia, ante a sagittis bibendum, elit risus ultricies sem, 18<sup>th</sup> sollicitudin malesuada massa magna nec ante. Donec et lacus nulla, ut interdum nunc. Sed interdum erat vitae mi consectetur eleifend. Aenean euismod justo vel felis lobortis sed ornare mi porta. Donec ut massa erat, sit amet molest</p>
<ul>
	<li>
		this is ugly</li>
	<li>
		I love SF</li>
	<li>
		Services</li>
	<li>
		tools</li>
</ul>
<p>ie nisl. Sed <a href="http://yahoo.com">lobortis</a> purus at nisi dapibus a egestas velit ornare. Nunc imperdiet, nibh ac lobortis adipiscing, ante tellus luctus sem, id volutpat sem mi nec est. Maecenas auctor rhoncus mauris, eu suscipit ante dictum in.</p>
<ol>
	<li>
		styling ordered lists</li>
	<li>
		blah blah blah....</li>
</ol>
<p>Etiam sollicitudin viverra justo, non feugiat enim cursus at. Praesent ut mi nec eros rhoncus mattis a sit amet ipsum. Donec eu diam non risus rutrum aliquet eget dictum nibh. Phasellus nec elit eget tellus volutpat dapibus. Morbi volutpat purus sit amet tellus pellentesque ut ornare orci pellentesque. Praesent ut consequat nulla. Nullam vel purus massa. Maecenas a velit vitae nisi porttitor auctor ac sit amet nisi. Maecenas ut turpis purus. Nunc turpis diam, accumsan et molestie eget, egestas nec lorem. Maecenas laoreet enim ut lorem lacinia congue. Donec quis lectus quam. Phasellus lobortis, turpis a feugiat egestas, risus enim ultricies arcu, non aliquet tellus augue a justo.</p>
\',
    \'teaser\' => \'<p>&nbsp;</p>
<p>Lorem <strong>ipsum dolor</strong> sit amet, consectetur adipiscing elit. Nunc sagittis sodales vulputate. Integer porttitor, eros id iaculis mollis, <em>urna felis </em>consequat quam, id tincidunt dolor turpis vel sem. <a name="new ancor">Quisque quis</a> pharetra ipsum. Fusce tempor consequat facilisis. Morbi eros lorem, porta a porta varius, feugiat vel magna. Sed vulputate vestibulum cursus. Aliquam a vulputate mi. In rutrum eleifend felis, non tempor lorem vulputate a.</p>\',
    \'log\' => \'\',
    \'revision_timestamp\' => NULL,
    \'format\' => \'1\',
    \'name\' => \'admin\',
    \'picture\' => \'\',
    \'data\' => \'a:0:{}\',
    \'path\' => NULL,
    \'field_about_image\' => array(
      \'0\' => NULL,
    ),
    \'field_resource\' => array(
      \'0\' => NULL,
    ),
    \'field_attachment\' => array(
      \'0\' => NULL,
    ),
    \'last_comment_timestamp\' => NULL,
    \'last_comment_name\' => NULL,
    \'comment_count\' => \'0\',
    \'taxonomy\' => array(),
    \'uuid\' => \'5e9faa8e-b0a8-11e1-ae37-0a27a7ce15fc\',
    \'revision_uuid\' => \'ae5cc9ec-cf59-11e1-be80-46e9befdb9a5\',
    \'menu\' => NULL,
    \'files\' => array(),
    \'#_export_node_encode_object\' => \'1\',
  ),
    array(
    \'nid\' => NULL,
    \'type\' => \'basic_page\',
    \'language\' => \'\',
    \'uid\' => \'1\',
    \'status\' => \'1\',
    \'created\' => NULL,
    \'changed\' => NULL,
    \'comment\' => \'0\',
    \'promote\' => \'0\',
    \'moderate\' => \'0\',
    \'sticky\' => \'0\',
    \'tnid\' => \'0\',
    \'translate\' => \'0\',
    \'vid\' => NULL,
    \'revision_uid\' => \'1\',
    \'title\' => \'Resources\',
    \'body\' => \'<p>&nbsp;</p>
<p><strong>Resources:</strong></p>
<ol>
	<li>
		How to pitch a tent</li>
	<li>
		asdfsdf</li>
	<li>
		asdfsdf</li>
	<li>
		&nbsp;</li>
</ol>
<p>&nbsp;</p>
<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc sagittis sodales vulputate. Integer porttitor, eros id iaculis mollis, urna felis consequat quam, id tincidunt dolor turpis vel sem. Quisque quis pharetra ipsum. Fusce tempor consequat facilisis. Morbi eros lorem, porta a porta varius, feugiat vel magna. Sed vulputate vestibulum cursus. Aliquam a vulputate mi. In rutrum eleifend felis, non tempor lorem vulputate a.</p>
<p>Nulla lacinia, ante a sagittis bibendum, elit risus ultricies sem, sollicitudin malesuada massa magna nec ante. Donec et lacus nulla, ut interdum nunc. Sed interdum erat vitae mi consectetur eleifend. Aenean euismod justo vel felis lobortis sed ornare mi porta. Donec ut massa erat, sit amet molestie nisl. Sed lobortis purus at nisi dapibus a egestas velit ornare. Nunc imperdiet, nibh ac lobortis adipiscing, ante tellus luctus sem, id volutpat sem mi nec est. Maecenas auctor rhoncus mauris, eu suscipit ante dictum in.</p>
<p>Etiam sollicitudin viverra justo, non feugiat enim cursus at. Praesent ut mi nec eros rhoncus mattis a sit amet ipsum. Donec eu diam non risus rutrum aliquet eget dictum nibh. Phasellus nec elit eget tellus volutpat dapibus. Morbi volutpat purus sit amet tellus pellentesque ut ornare orci pellentesque. Praesent ut consequat nulla. Nullam vel purus massa. Maecenas a velit vitae nisi porttitor auctor ac sit amet nisi. Maecenas ut turpis purus. Nunc turpis diam, accumsan et molestie eget, egestas nec lorem. Maecenas laoreet enim ut lorem lacinia congue. Donec quis lectus quam. Phasellus lobortis, turpis a feugiat egestas, risus enim ultricies arcu, non aliquet tellus augue a justo.</p>
\',
    \'teaser\' => \'<p>&nbsp;</p>
<p><strong>Resources:</strong></p>
<ol>
	<li>
		How to pitch a tent</li>
	<li>
		asdfsdf</li>
	<li>
		asdfsdf</li>
	<li>
		&nbsp;</li>
</ol>
<p>&nbsp;</p>\',
    \'log\' => \'\',
    \'revision_timestamp\' => NULL,
    \'format\' => \'1\',
    \'name\' => \'admin\',
    \'picture\' => \'\',
    \'data\' => \'a:0:{}\',
    \'path\' => NULL,
    \'field_about_image\' => array(
      \'0\' => NULL,
    ),
    \'field_resource\' => array(
      \'0\' => NULL,
    ),
    \'field_attachment\' => array(
      \'0\' => NULL,
    ),
    \'last_comment_timestamp\' => NULL,
    \'last_comment_name\' => NULL,
    \'comment_count\' => \'0\',
    \'taxonomy\' => array(),
    \'uuid\' => \'5e9fbd3a-b0a8-11e1-ae37-0a27a7ce15fc\',
    \'revision_uuid\' => \'ae6146ca-cf59-11e1-be80-46e9befdb9a5\',
    \'menu\' => NULL,
    \'files\' => array(),
    \'#_export_node_encode_object\' => \'1\',
  ),
    array(
    \'nid\' => NULL,
    \'type\' => \'basic_page\',
    \'language\' => \'\',
    \'uid\' => \'1\',
    \'status\' => \'1\',
    \'created\' => NULL,
    \'changed\' => NULL,
    \'comment\' => \'0\',
    \'promote\' => \'0\',
    \'moderate\' => \'0\',
    \'sticky\' => \'0\',
    \'tnid\' => \'0\',
    \'translate\' => \'0\',
    \'vid\' => NULL,
    \'revision_uid\' => \'1\',
    \'title\' => \'SR Online\',
    \'body\' => \'<p>&nbsp;</p>
<p style="text-align: justify; font-size: 11px; line-height: 14px; margin-bottom: 14px; font-family: Arial, Helvetica, sans; ">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc sagittis sodales vulputate. Integer porttitor, eros id iaculis mollis, urna felis consequat quam, id tincidunt dolor turpis vel sem. Quisque quis pharetra ipsum. Fusce tempor consequat facilisis. Morbi eros lorem, porta a porta varius, feugiat vel magna. Sed vulputate vestibulum cursus. Aliquam a vulputate mi. In rutrum eleifend felis, non tempor lorem vulputate a.</p>
<p style="text-align: justify; font-size: 11px; line-height: 14px; margin-bottom: 14px; font-family: Arial, Helvetica, sans; ">Nulla lacinia, ante a sagittis bibendum, elit risus ultricies sem, sollicitudin malesuada massa magna nec ante. Donec et lacus nulla, ut interdum nunc. Sed interdum erat vitae mi consectetur eleifend. Aenean euismod justo vel felis lobortis sed ornare mi porta. Donec ut massa erat, sit amet molestie nisl. Sed lobortis purus at nisi dapibus a egestas velit ornare. Nunc imperdiet, nibh ac lobortis adipiscing, ante tellus luctus sem, id volutpat sem mi nec est. Maecenas auctor rhoncus mauris, eu suscipit ante dictum in.</p>
<p style="text-align: justify; font-size: 11px; line-height: 14px; margin-bottom: 14px; font-family: Arial, Helvetica, sans; ">Etiam sollicitudin viverra justo, non feugiat enim cursus at. Praesent ut mi nec eros rhoncus mattis a sit amet ipsum. Donec eu diam non risus rutrum aliquet eget dictum nibh. Phasellus nec elit eget tellus volutpat dapibus. Morbi volutpat purus sit amet tellus pellentesque ut ornare orci pellentesque. Praesent ut consequat nulla. Nullam vel purus massa. Maecenas a velit vitae nisi porttitor auctor ac sit amet nisi. Maecenas ut turpis purus. Nunc turpis diam, accumsan et molestie eget, egestas nec lorem. Maecenas laoreet enim ut lorem lacinia congue. Donec quis lectus quam. Phasellus lobortis, turpis a feugiat egestas, risus enim ultricies arcu, non aliquet tellus augue a justo.</p>
\',
    \'teaser\' => \'<p>&nbsp;</p>
<p style="text-align: justify; font-size: 11px; line-height: 14px; margin-bottom: 14px; font-family: Arial, Helvetica, sans; ">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc sagittis sodales vulputate. Integer porttitor, eros id iaculis mollis, urna felis consequat quam, id tincidunt dolor turpis vel sem. Quisque quis pharetra ipsum. Fusce tempor consequat facilisis. Morbi eros lorem, porta a porta varius, feugiat vel magna. Sed vulputate vestibulum cursus. Aliquam a vulputate mi. In rutrum eleifend felis, non tempor lorem vulputate a.</p>\',
    \'log\' => \'\',
    \'revision_timestamp\' => NULL,
    \'format\' => \'1\',
    \'name\' => \'admin\',
    \'picture\' => \'\',
    \'data\' => \'a:0:{}\',
    \'path\' => NULL,
    \'field_about_image\' => array(
      \'0\' => NULL,
    ),
    \'field_resource\' => array(
      \'0\' => NULL,
    ),
    \'field_attachment\' => array(
      \'0\' => NULL,
    ),
    \'last_comment_timestamp\' => NULL,
    \'last_comment_name\' => NULL,
    \'comment_count\' => \'0\',
    \'taxonomy\' => array(),
    \'uuid\' => \'5e9fc6ea-b0a8-11e1-ae37-0a27a7ce15fc\',
    \'revision_uuid\' => \'ae64fd1a-cf59-11e1-be80-46e9befdb9a5\',
    \'menu\' => NULL,
    \'files\' => array(),
    \'#_export_node_encode_object\' => \'1\',
  ),
    array(
    \'nid\' => NULL,
    \'type\' => \'webform\',
    \'language\' => \'\',
    \'uid\' => \'1\',
    \'status\' => \'1\',
    \'created\' => NULL,
    \'changed\' => NULL,
    \'comment\' => \'0\',
    \'promote\' => \'1\',
    \'moderate\' => \'0\',
    \'sticky\' => \'0\',
    \'tnid\' => \'0\',
    \'translate\' => \'0\',
    \'vid\' => NULL,
    \'revision_uid\' => \'1\',
    \'title\' => \'Contact Us\',
    \'body\' => \'<p><span>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras sit amet elit non magna gravida vehicula. Integer congue rhoncus sem eu gravida. Fusce congue adipiscing odio, ac tincidunt erat ornare sed. Etiam gravida tortor id libero accumsan nec iaculis nibh laoreet.</span></p>
\',
    \'teaser\' => \'<p><span>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras sit amet elit non magna gravida vehicula. Integer congue rhoncus sem eu gravida. Fusce congue adipiscing odio, ac tincidunt erat ornare sed. Etiam gravida tortor id libero accumsan nec iaculis nibh laoreet.</span></p>
\',
    \'log\' => \'\',
    \'revision_timestamp\' => NULL,
    \'format\' => \'1\',
    \'name\' => \'admin\',
    \'picture\' => \'\',
    \'data\' => \'a:0:{}\',
    \'path\' => NULL,
    \'webform\' => array(
      \'nid\' => \'5\',
      \'confirmation\' => \'Thank you for your message. A member of the SR-Online staff will reply to your message by e-mail or telephone shortly.\',
      \'confirmation_format\' => \'1\',
      \'redirect_url\' => \'<none>\',
      \'status\' => \'1\',
      \'block\' => \'0\',
      \'teaser\' => \'0\',
      \'allow_draft\' => \'0\',
      \'auto_save\' => \'0\',
      \'submit_notice\' => \'0\',
      \'submit_text\' => \'\',
      \'submit_limit\' => \'-1\',
      \'submit_interval\' => \'-1\',
      \'total_submit_limit\' => \'-1\',
      \'total_submit_interval\' => \'-1\',
      \'record_exists\' => TRUE,
      \'roles\' => array(
        \'0\' => \'1\',
        \'1\' => \'2\',
      ),
      \'emails\' => array(),
      \'components\' => array(
        \'1\' => array(
          \'nid\' => \'5\',
          \'cid\' => \'1\',
          \'form_key\' => \'name\',
          \'name\' => \'Name\',
          \'type\' => \'textfield\',
          \'value\' => \'\',
          \'extra\' => array(
            \'title_display\' => \'before\',
            \'private\' => 0,
            \'disabled\' => 0,
            \'unique\' => 0,
            \'conditional_operator\' => \'=\',
            \'width\' => \'\',
            \'maxlength\' => \'\',
            \'field_prefix\' => \'\',
            \'field_suffix\' => \'\',
            \'description\' => \'\',
            \'attributes\' => array(),
            \'conditional_component\' => \'\',
            \'conditional_values\' => \'\',
          ),
          \'mandatory\' => \'1\',
          \'pid\' => \'0\',
          \'weight\' => \'0\',
          \'page_num\' => 1,
        ),
        \'2\' => array(
          \'nid\' => \'5\',
          \'cid\' => \'2\',
          \'form_key\' => \'email_address\',
          \'name\' => \'Email Address\',
          \'type\' => \'email\',
          \'value\' => \'\',
          \'extra\' => array(
            \'title_display\' => \'before\',
            \'private\' => 0,
            \'disabled\' => 0,
            \'unique\' => 0,
            \'conditional_operator\' => \'=\',
            \'width\' => \'\',
            \'description\' => \'\',
            \'attributes\' => array(),
            \'conditional_component\' => \'\',
            \'conditional_values\' => \'\',
          ),
          \'mandatory\' => \'1\',
          \'pid\' => \'0\',
          \'weight\' => \'1\',
          \'page_num\' => 1,
        ),
        \'3\' => array(
          \'nid\' => \'5\',
          \'cid\' => \'3\',
          \'form_key\' => \'telephone\',
          \'name\' => \'Telephone\',
          \'type\' => \'textfield\',
          \'value\' => \'\',
          \'extra\' => array(
            \'title_display\' => \'before\',
            \'private\' => 0,
            \'disabled\' => 0,
            \'unique\' => 0,
            \'conditional_operator\' => \'=\',
            \'width\' => \'\',
            \'maxlength\' => \'\',
            \'field_prefix\' => \'\',
            \'field_suffix\' => \'\',
            \'description\' => \'\',
            \'attributes\' => array(),
            \'conditional_component\' => \'\',
            \'conditional_values\' => \'\',
          ),
          \'mandatory\' => \'0\',
          \'pid\' => \'0\',
          \'weight\' => \'2\',
          \'page_num\' => 1,
        ),
        \'4\' => array(
          \'nid\' => \'5\',
          \'cid\' => \'4\',
          \'form_key\' => \'message\',
          \'name\' => \'Message\',
          \'type\' => \'textarea\',
          \'value\' => \'\',
          \'extra\' => array(
            \'title_display\' => 0,
            \'private\' => 0,
            \'resizable\' => 1,
            \'disabled\' => 0,
            \'conditional_operator\' => \'=\',
            \'cols\' => \'\',
            \'rows\' => \'\',
            \'description\' => \'\',
            \'attributes\' => array(),
            \'conditional_component\' => \'\',
            \'conditional_values\' => \'\',
          ),
          \'mandatory\' => \'1\',
          \'pid\' => \'0\',
          \'weight\' => \'3\',
          \'page_num\' => 1,
        ),
      ),
    ),
    \'last_comment_timestamp\' => NULL,
    \'last_comment_name\' => NULL,
    \'comment_count\' => \'0\',
    \'taxonomy\' => array(),
    \'uuid\' => \'b4d9fa12-ab26-11e1-a665-e89e5bed9625\',
    \'revision_uuid\' => \'ae684506-cf59-11e1-be80-46e9befdb9a5\',
    \'menu\' => NULL,
    \'files\' => array(),
    \'#_export_node_encode_object\' => \'1\',
  ),
    array(
    \'nid\' => NULL,
    \'type\' => \'basic_page\',
    \'language\' => \'\',
    \'uid\' => \'1\',
    \'status\' => \'1\',
    \'created\' => NULL,
    \'changed\' => NULL,
    \'comment\' => \'0\',
    \'promote\' => \'0\',
    \'moderate\' => \'0\',
    \'sticky\' => \'0\',
    \'tnid\' => \'0\',
    \'translate\' => \'0\',
    \'vid\' => NULL,
    \'revision_uid\' => \'1\',
    \'title\' => \'Terms of Use\',
    \'body\' => \'<p>&nbsp;</p>
<p style="text-align: justify; font-size: 11px; line-height: 14px; margin-bottom: 14px; font-family: Arial, Helvetica, sans; ">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc sagittis sodales vulputate. Integer porttitor, eros id iaculis mollis, urna felis consequat quam, id tincidunt dolor turpis vel sem. Quisque quis pharetra ipsum. Fusce tempor consequat facilisis. Morbi eros lorem, porta a porta varius, feugiat vel magna. Sed vulputate vestibulum cursus. Aliquam a vulputate mi. In rutrum eleifend felis, non tempor lorem vulputate a.</p>
<p style="text-align: justify; font-size: 11px; line-height: 14px; margin-bottom: 14px; font-family: Arial, Helvetica, sans; ">Nulla lacinia, ante a sagittis bibendum, elit risus ultricies sem, sollicitudin malesuada massa magna nec ante. Donec et lacus nulla, ut interdum nunc. Sed interdum erat vitae mi consectetur eleifend. Aenean euismod justo vel felis lobortis sed ornare mi porta. Donec ut massa erat, sit amet molestie nisl. Sed lobortis purus at nisi dapibus a egestas velit ornare. Nunc imperdiet, nibh ac lobortis adipiscing, ante tellus luctus sem, id volutpat sem mi nec est. Maecenas auctor rhoncus mauris, eu suscipit ante dictum in.</p>
<p style="text-align: justify; font-size: 11px; line-height: 14px; margin-bottom: 14px; font-family: Arial, Helvetica, sans; ">Etiam sollicitudin viverra justo, non feugiat enim cursus at. Praesent ut mi nec eros rhoncus mattis a sit amet ipsum. Donec eu diam non risus rutrum aliquet eget dictum nibh. Phasellus nec elit eget tellus volutpat dapibus. Morbi volutpat purus sit amet tellus pellentesque ut ornare orci pellentesque. Praesent ut consequat nulla. Nullam vel purus massa. Maecenas a velit vitae nisi porttitor auctor ac sit amet nisi. Maecenas ut turpis purus. Nunc turpis diam, accumsan et molestie eget, egestas nec lorem. Maecenas laoreet enim ut lorem lacinia congue. Donec quis lectus quam. Phasellus lobortis, turpis a feugiat egestas, risus enim ultricies arcu, non aliquet tellus augue a justo.</p>
\',
    \'teaser\' => \'<p>&nbsp;</p>
<p style="text-align: justify; font-size: 11px; line-height: 14px; margin-bottom: 14px; font-family: Arial, Helvetica, sans; ">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc sagittis sodales vulputate. Integer porttitor, eros id iaculis mollis, urna felis consequat quam, id tincidunt dolor turpis vel sem. Quisque quis pharetra ipsum. Fusce tempor consequat facilisis. Morbi eros lorem, porta a porta varius, feugiat vel magna. Sed vulputate vestibulum cursus. Aliquam a vulputate mi. In rutrum eleifend felis, non tempor lorem vulputate a.</p>\',
    \'log\' => \'\',
    \'revision_timestamp\' => NULL,
    \'format\' => \'1\',
    \'name\' => \'admin\',
    \'picture\' => \'\',
    \'data\' => \'a:0:{}\',
    \'path\' => NULL,
    \'field_about_image\' => array(
      \'0\' => NULL,
    ),
    \'field_resource\' => array(
      \'0\' => NULL,
    ),
    \'field_attachment\' => array(
      \'0\' => NULL,
    ),
    \'last_comment_timestamp\' => NULL,
    \'last_comment_name\' => NULL,
    \'comment_count\' => \'0\',
    \'taxonomy\' => array(),
    \'uuid\' => \'e3ae5006-b0ab-11e1-ae37-0a27a7ce15fc\',
    \'revision_uuid\' => \'ae6b4f1c-cf59-11e1-be80-46e9befdb9a5\',
    \'menu\' => NULL,
    \'files\' => array(),
    \'#_export_node_encode_object\' => \'1\',
  ),
    array(
    \'nid\' => NULL,
    \'type\' => \'basic_page\',
    \'language\' => \'\',
    \'uid\' => \'1\',
    \'status\' => \'1\',
    \'created\' => NULL,
    \'changed\' => NULL,
    \'comment\' => \'0\',
    \'promote\' => \'0\',
    \'moderate\' => \'0\',
    \'sticky\' => \'0\',
    \'tnid\' => \'0\',
    \'translate\' => \'0\',
    \'vid\' => NULL,
    \'revision_uid\' => \'1\',
    \'title\' => \'Privacy Policy\',
    \'body\' => \'<p>&nbsp;</p>
<p style="text-align: justify; font-size: 11px; line-height: 14px; margin-bottom: 14px; font-family: Arial, Helvetica, sans; ">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc sagittis sodales vulputate. Integer porttitor, eros id iaculis mollis, urna felis consequat quam, id tincidunt dolor turpis vel sem. Quisque quis pharetra ipsum. Fusce tempor consequat facilisis. Morbi eros lorem, porta a porta varius, feugiat vel magna. Sed vulputate vestibulum cursus. Aliquam a vulputate mi. In rutrum eleifend felis, non tempor lorem vulputate a.</p>
<p style="text-align: justify; font-size: 11px; line-height: 14px; margin-bottom: 14px; font-family: Arial, Helvetica, sans; ">Nulla lacinia, ante a sagittis bibendum, elit risus ultricies sem, sollicitudin malesuada massa magna nec ante. Donec et lacus nulla, ut interdum nunc. Sed interdum erat vitae mi consectetur eleifend. Aenean euismod justo vel felis lobortis sed ornare mi porta. Donec ut massa erat, sit amet molestie nisl. Sed lobortis purus at nisi dapibus a egestas velit ornare. Nunc imperdiet, nibh ac lobortis adipiscing, ante tellus luctus sem, id volutpat sem mi nec est. Maecenas auctor rhoncus mauris, eu suscipit ante dictum in.</p>
<p style="text-align: justify; font-size: 11px; line-height: 14px; margin-bottom: 14px; font-family: Arial, Helvetica, sans; ">Etiam sollicitudin viverra justo, non feugiat enim cursus at. Praesent ut mi nec eros rhoncus mattis a sit amet ipsum. Donec eu diam non risus rutrum aliquet eget dictum nibh. Phasellus nec elit eget tellus volutpat dapibus. Morbi volutpat purus sit amet tellus pellentesque ut ornare orci pellentesque. Praesent ut consequat nulla. Nullam vel purus massa. Maecenas a velit vitae nisi porttitor auctor ac sit amet nisi. Maecenas ut turpis purus. Nunc turpis diam, accumsan et molestie eget, egestas nec lorem. Maecenas laoreet enim ut lorem lacinia congue. Donec quis lectus quam. Phasellus lobortis, turpis a feugiat egestas, risus enim ultricies arcu, non aliquet tellus augue a justo.</p>
\',
    \'teaser\' => \'<p>&nbsp;</p>
<p style="text-align: justify; font-size: 11px; line-height: 14px; margin-bottom: 14px; font-family: Arial, Helvetica, sans; ">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc sagittis sodales vulputate. Integer porttitor, eros id iaculis mollis, urna felis consequat quam, id tincidunt dolor turpis vel sem. Quisque quis pharetra ipsum. Fusce tempor consequat facilisis. Morbi eros lorem, porta a porta varius, feugiat vel magna. Sed vulputate vestibulum cursus. Aliquam a vulputate mi. In rutrum eleifend felis, non tempor lorem vulputate a.</p>\',
    \'log\' => \'\',
    \'revision_timestamp\' => NULL,
    \'format\' => \'1\',
    \'name\' => \'admin\',
    \'picture\' => \'\',
    \'data\' => \'a:0:{}\',
    \'path\' => NULL,
    \'field_about_image\' => array(
      \'0\' => NULL,
    ),
    \'field_resource\' => array(
      \'0\' => NULL,
    ),
    \'field_attachment\' => array(
      \'0\' => NULL,
    ),
    \'last_comment_timestamp\' => NULL,
    \'last_comment_name\' => NULL,
    \'comment_count\' => \'0\',
    \'taxonomy\' => array(),
    \'uuid\' => \'ee2f2708-b0ab-11e1-ae37-0a27a7ce15fc\',
    \'revision_uuid\' => \'ae6eedd4-cf59-11e1-be80-46e9befdb9a5\',
    \'menu\' => NULL,
    \'files\' => array(),
    \'#_export_node_encode_object\' => \'1\',
  ),
)',
);
  return $node_export;
}
