<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
<title>MakeTime for Arabic/Islamic Higri Calendar</title>
<meta http-equiv="Content-Type" content="text/html;charset=utf-8" />
<link rel="stylesheet" type="text/css" href="style.css" media="all" />
</head>

<body>

<div class="Paragraph">
<h2 dir="ltr">Example Output:</h2>

<?php
    error_reporting(E_STRICT);
    $time_start = microtime(true);
    
    date_default_timezone_set('UTC');
    
    include('../Arabic.php');
    $Ar = new Arabic('ArMktime');

    $correction = $Ar->mktimeCorrection(9, 1429);
    $time = $Ar->mktime(0, 0, 0, 9, 1, 1429, $correction);
    
    echo "Calculated first day of Ramadan 1429 unix timestamp is: $time<br>";
    
    $Gregorian = date('l F j, Y',$time);
    
    echo "Which is $Gregorian in Gregorian calendar";
?>
</div><br />
<div class="Paragraph">
<h2>Example Code:</h2>
<?php
    highlight_string(<<<'END'
<?php
    date_default_timezone_set('UTC');
    
    include('../Arabic.php');
    $Ar = new Arabic('ArMktime');

    $correction = $Ar->mktimeCorrection(9, 1429);
    $time = $Ar->mktime(0, 0, 0, 9, 1, 1429, $correction);
    
    echo "Calculated first day of Ramadan 1429 unix timestamp is: $time<br>";
    
    $Gregorian = date('l F j, Y',$time);
    
    echo "Which is $Gregorian in Gregorian calendar";
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
<a href="../Documentation/Arabic/_sub---ArMktime.class.php.html" target="_blank">Related Class Documentation</a>
</div>
</body>
</html>
