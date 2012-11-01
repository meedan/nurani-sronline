<?php
/**
 * ----------------------------------------------------------------------
 *  
 * Copyright (c) 2006-2011 Khaled Al-Sham'aa.
 *  
 * http://www.ar-php.org
 *  
 * PHP Version 5 
 *  
 * ----------------------------------------------------------------------
 *  
 * LICENSE
 *
 * This program is open source product; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License (LGPL)
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *  
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/lgpl.txt>.
 *  
 * ----------------------------------------------------------------------
 *  
 * Class Name: Arabic StrToTime Class
 *  
 * Filename: ArStrToTime.class.php
 *  
 * Original  Author(s): Khaled Al-Sham'aa <khaled@ar-php.org>
 *  
 * Purpose:  Parse about any Arabic textual datetime description into 
 *           a Unix timestamp
 *  
 * ----------------------------------------------------------------------
 *  
 * Arabic StrToTime Class
 *
 * PHP class to parse about any Arabic textual datetime description into 
 * a Unix timestamp.
 * 
 * The function expects to be given a string containing an Arabic date format 
 * and will try to parse that format into a Unix timestamp (the number of seconds 
 * since January 1 1970 00:00:00 GMT), relative to the timestamp given in now, or 
 * the current time if none is supplied.
 *          
 * Example:
 * <code>
 *     date_default_timezone_set('UTC');
 *     $time = time();
 * 
 *     echo date('l dS F Y', $time);
 *     echo '<br /><br />';
 * 
 *     include('./Arabic.php');
 *     $obj = new Arabic('ArStrToTime');
 * 
 *     $int  = $obj->strtotime($str, $time);
 *     $date = date('l dS F Y', $int);
 *     echo "<b><font color=#FFFF00>Arabic String:</font></b> $str<br />";
 *     echo "<b><font color=#FFFF00>Unix Timestamp:</font></b> $int<br />";
 *     echo "<b><font color=#FFFF00>Formated Date:</font></b> $date<br />";    
 * </code>
 *          
 * @category  I18N 
 * @package   Arabic
 * @author    Khaled Al-Sham'aa <khaled@ar-php.org>
 * @copyright 2006-2011 Khaled Al-Sham'aa
 *    
 * @license   LGPL <http://www.gnu.org/licenses/lgpl.txt>
 * @link      http://www.ar-php.org 
 */

// New in PHP V5.3: Namespaces
// namespace I18N\Arabic;
// 
// $obj = new I18N\Arabic\ArStrToTime();
// 
// use I18N\Arabic;
// $obj = new Arabic\ArStrToTime();
//
// use I18N\Arabic\ArStrToTime as StrToTime;
// $obj = new StrToTime();

/**
 * This PHP class parse about any Arabic textual datetime description into a 
 * Unix timestamp
 *  
 * @category  I18N 
 * @package   Arabic
 * @author    Khaled Al-Sham'aa <khaled@ar-php.org>
 * @copyright 2006-2011 Khaled Al-Sham'aa
 *    
 * @license   LGPL <http://www.gnu.org/licenses/lgpl.txt>
 * @link      http://www.ar-php.org 
 */ 
class ArStrToTime
{
    protected static $hj = array();
                               
    protected static $strtotimeSearch  = array();
    protected static $strtotimeReplace = array();
    
    /**
     * "strtotime" method input charset
     * @var String     
     */         
    public $strtotimeInput = 'utf-8';

    /**
     * Name of the textual "strtotime" method parameters 
     * @var Array     
     */         
    public $strtotimeVars = array('text');

    /**
     * Loads initialize values
     */         
    public function __construct()
    {
        $xml = simplexml_load_file(dirname(__FILE__).'/data/ArStrToTime.xml');
    
        foreach ($xml->xpath("//str_replace[@function='strtotime']/pair") as $pair) {
            array_push(self::$strtotimeSearch, (string)$pair->search);
            array_push(self::$strtotimeReplace, (string)$pair->replace);
        } 

        foreach ($xml->hj_month->month as $month) {
            array_push(self::$hj, (string)$month);
        } 
    }
    
    /**
     * This method will parse about any Arabic textual datetime description into 
     * a Unix timestamp
     *          
     * @param string  $text The string to parse, according to the GNU » 
     *                      Date Input Formats syntax (in Arabic).
     * @param integer $now  The timestamp used to calculate the 
     *                      returned value.       
     *                    
     * @return Integer Returns a timestamp on success, FALSE otherwise
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public static function strtotime($text, $now)
    {
        $int = 0;

        for ($i=0; $i<12; $i++) {
            if (strpos($text, self::$hj[$i]) > 0) {
                preg_match('/.*(\d{1,2}).*(\d{4}).*/', $text, $matches);

                include dirname(__FILE__).'/ArMktime.class.php';
                $temp = new ArMktime();
                $int  = $temp->mktime(0, 0, 0, $i+1, $matches[1], $matches[2]);
                $temp = null;

                break;
            }
        }

        if ($int == 0) {
            $patterns     = array();
            $replacements = array();
  
            array_push($patterns, '/َ|ً|ُ|ٌ|ِ|ٍ|ْ|ّ/');
            array_push($replacements, '');
  
            array_push($patterns, '/\s*ال(\S{3,})\s+ال(\S{3,})/');
            array_push($replacements, ' \\2 \\1');
  
            array_push($patterns, '/\s*ال(\S{3,})/');
            array_push($replacements, ' \\1');
  
            $text = preg_replace($patterns, $replacements, $text);

            $text = str_replace(self::$strtotimeSearch, 
                                self::$strtotimeReplace, $text);
  
            $pattern = '[ابتثجحخدذرزسشصضطظعغفقكلمنهوي]';
            $text    = preg_replace("/$pattern/", '', $text);

            $int = strtotime($text, $now);
        }
        
        return $int;
    }
}