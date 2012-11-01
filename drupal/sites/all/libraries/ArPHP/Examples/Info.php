<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
<title>Arabic Countries Information</title>
<meta http-equiv="Content-Type" content="text/html;charset=utf-8" />
<link rel="stylesheet" type="text/css" href="style.css" media="all" />
</head>

<body>

<div class="Paragraph">
<h2 dir="ltr">SimpleXML Example Output:</h2>
<?php
    error_reporting(E_STRICT);
    $time_start = microtime(true);

    // set name of XML file
    $file = '../sub/lists/arab_countries.xml';
    
    // load XML file
    $xml = simplexml_load_file($file) or die ('Unable to load XML file!');

    if($_GET['lang'] == 'arabic') {
        $lang = 'arabic';
        echo '<a href="Info.php?lang=english">English</a>';
    } else {
        $lang = 'english';
        echo '<a href="Info.php?lang=arabic">Arabic</a>';
    }
    
    echo '<table width="98%" cellpadding="5" cellspacing="2">';

    echo '<tr>';
    echo '<td><b><u>Country</u></b></td>';
    echo '<td><b><u>Capital</u></b></td>';
    echo '<td><b><u>Time Zone</u></b></td>';
    echo '<td><b><u>Time</u></b></td>';
    echo '<td><b><u>Currency</u></b></td>';
    echo '<td><b><u>Local Domain</u></b></td>';
    echo '<td><b><u>Dial Codes</u></b></td>';
    echo '</tr>';
    
    // iterate over <country> element collection
    foreach ($xml as $country) {
        echo ($i++ % 2)? '<tr bgcolor="#F5F5F5">' : '<tr bgcolor="#E5E5E5">';
        
        echo '<td><a href="../sub/lists/'.$country->name->english.'.png" target="_blank">'.$country->name->$lang.'</a></td>';

        $lat = substr($country->capital->latitude, 0, -3);
        if(substr($country->capital->latitude, -1) == 'S') $lat = -1 * $lat;
        
        $lon = substr($country->capital->longitude, 0, -3);
        if(substr($country->capital->latitude, -1) == 'W') $lon = -1 * $lon;

        echo '<td><a href="http://maps.google.com/maps?ll='.$lat.','.$lon.'&t=h&z=10" target="_blank">'.$country->capital->$lang.'</a></td>';

        $timezone = $country->timezone;
        if ($country->summertime['used'] == 'true') {
            $start = strtotime($country->summertime->start);
            $end   = strtotime($country->summertime->end);
            if (time() > $start && time() < $end) {
                $timezone = $timezone + 1;
                $timezone = '+' . $timezone;
            }
        }
        
        echo '<td>'.$timezone.' GMT</td>';
        echo '<td>'.date('G:i', time()+$timezone*3600).'</td>';
        echo '<td><a href="http://www.xe.com/ucc/convert.cgi?Amount=1&From=USD&To='.$country->currency->iso.'" target="_blank">'.$country->currency->$lang.'</a></td>';
        echo '<td><a href="http://www.101domain.com/whois-'.strtolower($country->iso3166->a2).'.php" target="_blank">http://www.example.com.'.strtolower($country->iso3166->a2).'</a></td>';
        echo '<td>+'.$country->dialcode.'</td>';
        echo '</tr>';
    }

    echo '</table>';
    $xml = null;
?>
</div><br />

<div class="Paragraph">
<h2>SimpleXML Example Code:</h2>
<?php
highlight_string(<<<'END'
<?php
    // set name of XML file
    $file = '../sub/lists/arab_countries.xml';
    
    // load XML file
    $xml = simplexml_load_file($file) or die ('Unable to load XML file!');

    if($_GET['lang'] == 'arabic') {
        $lang = 'arabic';
        echo '<a href="Info.php?lang=english">English</a>';
    } else {
        $lang = 'english';
        echo '<a href="Info.php?lang=arabic">Arabic</a>';
    }
    
    echo '<table width="98%" cellpadding="5" cellspacing="2">';

    echo '<tr>';
    echo '<td><b><u>Country</u></b></td>';
    echo '<td><b><u>Capital</u></b></td>';
    echo '<td><b><u>Time Zone</u></b></td>';
    echo '<td><b><u>Time</u></b></td>';
    echo '<td><b><u>Currency</u></b></td>';
    echo '<td><b><u>Local Domain</u></b></td>';
    echo '<td><b><u>Dial Codes</u></b></td>';
    echo '</tr>';
    
    // iterate over <country> element collection
    foreach ($xml as $country) {
        echo ($i++ % 2)? '<tr bgcolor="#F5F5F5">' : '<tr bgcolor="#E5E5E5">';
        
        echo '<td><a href="../sub/lists/'.$country->name->english.'.png" target="_blank">'.$country->name->$lang.'</a></td>';

        $lat = substr($country->capital->latitude, 0, -3);
        if(substr($country->capital->latitude, -1) == 'S') $lat = -1 * $lat;
        
        $lon = substr($country->capital->longitude, 0, -3);
        if(substr($country->capital->latitude, -1) == 'W') $lon = -1 * $lon;

        echo '<td><a href="http://maps.google.com/maps?ll='.$lat.','.$lon.'&t=h&z=10" target="_blank">'.$country->capital->$lang.'</a></td>';

        $timezone = $country->timezone;
        if ($country->summertime['used'] == 'true') {
            $start = strtotime($country->summertime->start);
            $end   = strtotime($country->summertime->end);
            if (time() > $start && time() < $end) {
                $timezone = $timezone + 1;
                $timezone = '+' . $timezone;
            }
        }
        
        echo '<td>'.$timezone.' GMT</td>';
        echo '<td>'.date('G:i', time()+$timezone*3600).'</td>';
        echo '<td><a href="http://www.xe.com/ucc/convert.cgi?Amount=1&From=USD&To='.$country->currency->iso.'" target="_blank">'.$country->currency->$lang.'</a></td>';
        echo '<td><a href="http://www.101domain.com/whois-'.strtolower($country->iso3166->a2).'.php" target="_blank">http://www.example.com.'.strtolower($country->iso3166->a2).'</a></td>';
        echo '<td>+'.$country->dialcode.'</td>';
        echo '</tr>';
    }

    echo '</table>';
    $xml = null;
END
);

    $time_end = microtime(true);
    $time = $time_end - $time_start;
    
    echo "<hr />Total execution time is $time seconds<br />\n";
    echo 'Amount of memory allocated to this script is ' . memory_get_usage() . ' bytes';

    $included_files = get_included_files();
    echo '<h4>Names of included or required files:</h4><ul>';
    
    foreach ($included_files as $filename) {
        echo "<li>$filename</li>";
    }

    echo '</ul>';
?>
</div>

</body>
</html>
