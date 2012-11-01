<?php
/**
 * ----------------------------------------------------------------------
 *  
 * Copyright (c) 2006-2011 Khaled Al-Sham'aa
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
 * Class Name: Muslim Prayer Times
 *  
 * Filename:   Salat.class.php
 *  
 * Original    Author(s): Khaled Al-Sham'aa <khaled@ar-php.org>
 *  
 * Purpose:    The five Islamic prayers are named Fajr, Zuhr, Asr, Maghrib
 *             and Isha. The timing of these five prayers varies from place
 *             to place and from day to day. It is obligatory for Muslims
 *             to perform these prayers at the correct time.
 *              
 * ----------------------------------------------------------------------
 *  
 * Source: http://qasweb.org/qasforum/index.php?showtopic=177&st=0
 * By: Mohamad Magdy <mohamad_magdy_egy@hotmail.com>
 *  
 * ----------------------------------------------------------------------
 *  
 * Muslim Prayer Times
 *
 * Using this PHP Class you can calculate the time of Muslim prayer
 * according to the geographic location.
 * 
 * The five Islamic prayers are named Fajr, Zuhr, Asr, Maghrib and Isha. The timing 
 * of these five prayers varies from place to place and from day to day. It is 
 * obligatory for Muslims to perform these prayers at the correct time.
 * 
 * The prayer times for any given location on earth may be determined mathematically 
 * if the latitude and longitude of the location are known. However, the theoretical 
 * determination of prayer times is a lengthy process. Much of this tedium may be 
 * alleviated by using computer programs.
 * 
 * Definition of prayer times
 * 
 * - FAJR starts with the dawn or morning twilight. Fajr ends just before sunrise.
 * - ZUHR begins after midday when the trailing limb of the sun has passed the 
 *   meridian. For convenience, many published prayer timetables add five minutes to 
 *   mid-day (zawal) to obtain the start of Zuhr. Zuhr ends at the start of Asr time.
 * - The timing of ASR depends on the length of the shadow cast by an object. 
 *   According to the Shafi school of jurisprudence, Asr begins when the length of 
 *   the shadow of an object exceeds the length of the object. According to the 
 *   Hanafi school of jurisprudence, Asr begins when the length of the shadow 
 *   exceeds TWICE the length of the object. In both cases, the minimum length of 
 *   shadow (which occurs when the sun passes the meridian) is subtracted from the 
 *   length of the shadow before comparing it with the length of the object.
 * - MAGHRIB begins at sunset and ends at the start of isha.
 * - ISHA starts after dusk when the evening twilight disappears.      
 *
 * Example:
 * <code>
 *     date_default_timezone_set('UTC');
 *     
 *     include('./Arabic.php');
 *     $obj = new Arabic('Salat');
 * 
 *     $obj->setLocation(33.513,36.292,2);
 *     $obj->setDate(date('j'), date('n'), date('Y'));
 * 
 *     $times = $obj->getPrayTime();
 * 
 *     echo '<b>Damascus, Syria</b><br />';
 *     echo date('l F j, Y').'<br /><br />';
 *        
 *     echo "<b class=hilight>Fajr:</b> {$times[0]}<br />";
 *     echo "<b class=hilight>Sunrise:</b> {$times[1]}<br />";
 *     echo "<b class=hilight>Zuhr:</b> {$times[2]}<br />";
 *     echo "<b class=hilight>Asr:</b> {$times[3]}<br />";
 *     echo "<b class=hilight>Maghrib:</b> {$times[4]}<br />";
 *     echo "<b class=hilight>Isha:</b> {$times[5]}<br />";    
 * </code>
 * 
 * Qibla Determination Methods - Basic Spherical Trigonometric Formula
 * 
 * The problem of qibla determination has a simple formulation in spherical 
 * trigonometry. A is a given location, K is the Ka'ba, and N is the North Pole. 
 * The great circle arcs AN and KN are along the meridians through A and K, 
 * respectively, and both point to the north. The qibla is along the great circle 
 * arc AK. The spherical angle q = NAK is the angle at A from the north direction 
 * AN to the direction AK towards the Ka'ba, and so q is the qibla bearing to be 
 * computed. Let F and L be the latitude and longitude of A, and FK and LK be 
 * the latitude and longitude of K (the Ka'ba). If all angles and arc lengths 
 * are measured in degrees, then it is seen that the arcs AN and KN are of measure 
 * 90 - F and 90 - FK, respectively. Also, the angle ANK between the meridians 
 * of K and A equals the difference between the longitudes of A and K, that is, 
 * LK - L, no matter what the prime meridian is. Here we are given two sides and 
 * the included angle of a spherical triangle, and it is required to determine one 
 * other angle. One of the simplest solutions is given by the formula:
 * <pre> 
 *                       -1              sin(LK - L)
 *                q = tan   ------------------------------------------
 *                              cos F tan FK - sin F cos(LK - L) 
 * </pre>
 * In this Equation, the sign of the input quantities are assumed as follows: 
 * latitudes are positive if north, negative if south; longitudes are positive 
 * if east, negative if west. The quadrant of q is assumed to be so selected 
 * that sin q and cos q have the same sign as the numerator and denominator of 
 * this Equation. With these conventions, q will be positive for bearings east 
 * of north, negative for bearings west of north.
 * 
 * Reference:
 * The Correct Qibla, S. Kamal Abdali <k.abdali@acm.org>
 * PDF version in http://www.patriot.net/users/abdali/ftp/qibla.pdf    
 *
 * Example:
 * <code>
 *     date_default_timezone_set('UTC');
 *     
 *     include('./Arabic.php');
 *     $obj = new Arabic('Salat');
 * 
 *     $obj->setLocation(33.513,36.292,2);
 *
 *     $direction = $obj->getQibla();
 *     echo "<b>Qibla Direction (from the north direction):</b> $direction<br />";
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
// $obj = new I18N\Arabic\Salat();
// 
// use I18N\Arabic;
// $obj = new Arabic\Salat();
//
// use I18N\Arabic\Salat as Salat;
// $obj = new Salat();

/**
 * This PHP class calculate the time of Muslim prayer according to the geographic 
 * location.
 *  
 * @category  I18N 
 * @package   Arabic
 * @author    Khaled Al-Sham'aa <khaled@ar-php.org>
 * @copyright 2006-2011 Khaled Al-Sham'aa
 *    
 * @license   LGPL <http://www.gnu.org/licenses/lgpl.txt>
 * @link      http://www.ar-php.org 
 */ 
class Salat
{
    // السنة
    protected $year = 1975;
    
    // الشهر
    protected $month = 8;
    
    // اليوم
    protected $day = 2;
    
    // فرق التوقيت العالمى
    protected $zone = 2;
    
    // خط الطول الجغرافى للمكان
    protected $long = 37.15861;
    
    // خط العرض الجغرافى
    protected $lat = 36.20278;
    
    // زاوية الشروق والغروب
    protected $AB2 = -0.833333;

    // زاوية العشاء
    protected $AG2 = -18;
    
    // زاوية الفجر
    protected $AJ2 = -18;
    
    // المذهب
    protected $school = 'Shafi';
    
    // الطائفة
    protected $view = 'Sunni';

    /**
     * Loads initialize values
     */         
    public function __construct()
    {
    }
        
    /**
     * Setting date of day for Salat calculation
     *      
     * @param integer $d Day of date you want to calculate Salat in
     * @param integer $m Month of date you want to calculate Salat in
     * @param integer $y Year (four digits) of date you want to calculate Salat in
     *      
     * @return object $this to build a fluent interface
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public function setDate($d = 2, $m = 8, $y = 1975)
    {
        if (is_numeric($y) && $y > 0 && $y < 3000) {
            $this->year = floor($y);
        }
        
        if (is_numeric($m) && $m >= 1 && $m <= 12) {
            $this->month = floor($m);
        }
        
        if (is_numeric($d) && $d >= 1 && $d <= 31) {
            $this->day = floor($d);
        }
        
        return $this;
    }
    
    /**
     * Setting location information for Salat calculation
     *      
     * @param decimal $l1 Longitude of location you want to calculate Salat time in
     * @param decimal $l2 Latitude of location you want to calculate Salat time in
     * @param integer $z  Time Zone, offset from UTC (see also Greenwich Mean Time)
     *      
     * @return object $this to build a fluent interface
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public function setLocation($l1 = 37.15861, $l2 = 36.20278, $z = 2)
    {
        if (is_numeric($l1) && $l1 >= -180 && $l1 <= 180) {
            $this->long = $l1;
        }
        
        if (is_numeric($l2) && $l2 >= -180 && $l2 <= 180) {
            $this->lat = $l2;
        }
        
        if (is_numeric($z) && $z >= -12 && $z <= 12) {
            $this->zone = floor($z);
        }
        
        return $this;
    }
    
    /**
     * Setting rest of Salat calculation configuration
     * 
     * Convention 	                              Fajr Angle  Isha Angle
     * 
     * Muslim World League 	                            -18 	  -17
     *      
     * Islamic Society of North America (ISNA) 	        -15 	  -15
     *      
     * Egyptian General Authority of Survey 	          -19.5 	-17.5
     *      
     * Umm al-Qura University, Makkah 	                -18.5 	
     * Isha 90  min after Maghrib, 120 min during Ramadan
     *      
     * University of Islamic Sciences, Karachi 	        -18 	  -18
     *      
     * Institute of Geophysics, University of Tehran 	  -17.7 	-14(*)
     *      
     * Shia Ithna Ashari, Leva Research Institute, Qum 	-16 	  -14
     * 
     * (*) Isha angle is not explicitly defined in Tehran method
     * Fajr Angle = $fajrArc, Isha Angle = $ishaArc     
     *                 
     * - حزب العلماء في لندن لدول
     * أوروبا في خطوط عرض تزيد على 48
     *       
     *      $ishaArc = -17
     *      $fajrArc = -17
     *      
     * @param string  $sch        [Shafi|Hanafi] to define Muslims Salat 
     *                            calculation method (affect Asr time)
     * @param decimal $sunriseArc Sun rise arc (default value is -0.833333)
     * @param decimal $ishaArc    Isha arc (default value is -18)
     * @param decimal $fajrArc    Fajr arc (default value is -18)
     * @param string  $view       [Sunni|Shia] to define Muslims Salat calculation
     *                            method (affect Maghrib and Midnight time)
     *      
     * @return object $this to build a fluent interface
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public function setConf($sch = 'Shafi', $sunriseArc = -0.833333, 
                            $ishaArc = -17.5, $fajrArc = -19.5, $view = 'Sunni')
    {
        $sch = ucfirst($sch);
        
        if ($sch == 'Shafi' || $sch == 'Hanafi') {
            $this->school = $sch;
        }
        
        if (is_numeric($sunriseArc) && $sunriseArc >= -180 && $sunriseArc <= 180) {
            $this->AB2 = $sunriseArc;
        }
        
        if (is_numeric($ishaArc) && $ishaArc >= -180 && $ishaArc <= 180) {
            $this->AG2 = $ishaArc;
        }
        
        if (is_numeric($fajrArc) && $fajrArc >= -180 && $fajrArc <= 180) {
            $this->AJ2 = $fajrArc;
        }
        
        if ($view == 'Sunni' || $view == 'Shia') {
            $this->view = $view;
        }
        
        return $this;
    }
    
    /**
     * Calculate Salat times for the date set in setSalatDate methode, and 
     * location set in setSalatLocation.
     *                        
     * @return array of Salat times + sun rise in the following format
     *               hh:mm where hh is the hour in local format and 24 mode
     *               mm is minutes with leading zero to be 2 digits always
     *               array items is [Fajr, Sunrise, Zuhr, Asr, Maghrib, Isha]
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     * @author Mohamad Magdy <mohamad_magdy_egy@hotmail.com>
     * @source http://qasweb.org/qasforum/index.php?showtopic=177&st=0
     */
    public function getPrayTime()
    {
        $prayTime = array();
        
        // نحسب اليوم الجوليانى
        $d = ((367 * $this->year) - (floor((7 / 4) * ($this->year + 
             floor(($this->month + 9) / 12)))) + floor(275 * ($this->month / 9)) + 
             $this->day - 730531.5);
        
        // نحسب طول الشمس الوسطى
        $L = fmod(280.461 + 0.9856474 * $d, 360);
        
        // ثم نحسب حصة الشمس الوسطى
        $M = fmod(357.528 + 0.9856003 * $d, 360);
        
        // ثم نحسب طول الشمس البروجى
        $lambda = $L + 1.915 * sin($M * pi() / 180) + 
                  0.02 * sin(2 * $M * pi() / 180);
        
        // ثم نحسب ميل دائرة البروج
        $obl = 23.439 - 0.0000004 * $d;
        
        // ثم نحسب المطلع المستقيم
        $alpha = atan(cos($obl * pi() / 180) * tan($lambda * pi() / 180)) * 
                 180 / pi();
        $alpha = $alpha - (360 * floor($alpha / 360));
        
        // ثم نعدل المطلع المستقيم
        $alpha = $alpha + 90 * ((int)($lambda / 90) - (int)($alpha / 90));
        
        // نحسب الزمن النجمى بالدرجات الزاوية
        $ST = fmod(100.46 + 0.985647352 * $d, 360);
        
        // ثم نحسب ميل الشمس الزاوى
        $Dec = asin(sin($obl * pi() / 180) * sin($lambda * pi() / 180)) * 180 / pi();
        
        // نحسب زوال الشمس الوسطى
        $noon = fmod(abs($alpha - $ST), 360);
        
        // ثم الزوالى العالمى
        $un_noon = $noon - $this->long;
        
        // ثم الزوال المحلى
        $local_noon = fmod(($un_noon/15) + $this->zone, 24);
        
        // وقت صلاة الظهر
        $Dhuhr       = $local_noon / 24;
        $Dhuhr_h     = (int)($Dhuhr * 24 * 60 / 60);
        $Dhuhr_m     = sprintf('%02d', ($Dhuhr * 24 * 60) % 60);
        $prayTime[2] = $Dhuhr_h.':'.$Dhuhr_m;
        
        if ($this->school == 'Shafi') {
            // نحسب إرتفاع الشمس لوقت صلاة العصر
            // حسب المذهب الشافعي
            $T = atan(1 + tan(abs($this->lat - $Dec) * pi() / 180)) * 180 / pi();
            
            // ثم نحسب قوس الدائر أى الوقت المتبقى
            // من وقت الظهر حتى صلاة العصر
            // حسب المذهب الشافعي
            $V = acos((sin((90 - $T) * pi() / 180) - sin($Dec * pi() / 180) * 
                 sin($this->lat * pi() / 180)) / (cos($Dec * pi() / 180) * 
                 cos($this->lat * pi() / 180))) * 180 / pi() / 15;
            
            // وقت صلاة العصر حسب المذهب الشافعي
            $X           = $local_noon + $V;
            $SAsr        = $Dhuhr + $V / 24;
            $SAsr_h      = (int)($SAsr * 24 * 60 / 60);
            $SAsr_m      = sprintf('%02d', ($SAsr * 24 * 60) % 60);
            $prayTime[3] = $SAsr_h.':'.$SAsr_m;
        } else {
            // نحسب إرتفاع الشمس لوقت صلاة العصر
            // حسب المذهب الحنفي
            $U = atan(2 + tan(abs($this->lat - $Dec) * pi() / 180)) * 180 / pi();
            
            // ثم نحسب قوس الدائر أى الوقت المتبقى
            // من وقت الظهر حتى صلاة العصر
            // حسب المذهب الحنفي
            $W = acos((sin((90 - $U) * pi() / 180) - sin($Dec * pi() / 180) * 
                 sin($this->lat * pi() / 180)) / (cos($Dec * pi() / 180) * 
                 cos($this->lat * pi() / 180))) * 180 / pi() / 15;
            
            // وقت صلاة العصر حسب المذهب الحنفي
            $Z           = $local_noon + $W;
            $HAsr        = $Z / 24;
            $HAsr_h      = (int)($HAsr * 24 * 60 / 60);
            $HAsr_m      = sprintf('%02d', ($HAsr * 24 * 60) % 60);
            $prayTime[3] = $HAsr_h.':'.$HAsr_m;
        }
        
        // نحسب نصف قوس النهار
        $AB = acos((SIN($this->AB2 * pi() / 180) - sin($Dec * pi() / 180) * 
              sin($this->lat * pi() / 180)) / (cos($Dec * pi() / 180) * 
              cos($this->lat * pi() / 180))) * 180 / pi();
        
        // وقت الشروق
        $AC          = $local_noon - $AB / 15;
        $Sunrise     = $AC / 24;
        $Sunrise_h   = (int)($Sunrise * 24 * 60 / 60);
        $Sunrise_m   = sprintf('%02d', ($Sunrise * 24 * 60) % 60);
        $prayTime[1] = $Sunrise_h.':'.$Sunrise_m;
        
        // وقت الغروب
        $AE          = $local_noon + $AB / 15;
        $Sunset      = $AE / 24;
        $Sunset_h    = (int)($Sunset * 24 * 60 / 60);
        $Sunset_m    = sprintf('%02d', ($Sunset * 24 * 60) % 60);
        $prayTime[4] = $Sunset_h.':'.$Sunset_m;
        
        // نحسب فضل الدائر وهو الوقت المتبقى
        // من وقت صلاة الظهر إلى وقت العشاء
        $AG = acos((sin($this->AG2 * pi() / 180) - sin($Dec * pi() / 180) * 
              sin($this->lat * pi() / 180)) / (cos($Dec * pi() / 180) * 
              cos($this->lat * pi() / 180))) * 180 / pi();
        
        // وقت صلاة العشاء
        $AH          = $local_noon + ($AG / 15);
        $Isha        = $AH / 24;
        $Isha_h      = (int)($Isha * 24 * 60 / 60);
        $Isha_m      = sprintf('%02d', ($Isha * 24 * 60) % 60);
        $prayTime[5] = $Isha_h.':'.$Isha_m;
        
        // نحسب فضل دائر الفجر وهو الوقت المتبقى
        // من وقت صلاة الفجر حتى وقت صلاة الظهر
        $AJ = acos((sin($this->AJ2 * pi() / 180) - sin($Dec * pi() / 180) * 
              sin($this->lat * pi() / 180)) / (cos($Dec * pi() / 180) * 
              cos($this->lat * pi() / 180))) * 180 / pi();
        
        // وقت صلاة الفجر
        $AK          = $local_noon - $AJ / 15;
        $Fajr        = $AK / 24;
        $Fajr_h      = (int)($Fajr * 24 * 60 / 60);
        $Fajr_m      = sprintf('%02d', ($Fajr * 24 * 60) % 60);
        $prayTime[0] = $Fajr_h.':'.$Fajr_m;
        
        return $prayTime;
    }
    
    /**
     * Another algorithm (more accurate) to calculate Salat times for the date 
     * set in setSalatDate methode, and location set in setSalatLocation.
     *                        
     * @return array of Salat times + sun rise in the following format
     *               hh:mm where hh is the hour in local format and 24 mode
     *               mm is minutes with leading zero to be 2 digits always
     *               array items is [$Fajr, $Sunrise, $Dhuhr, $Asr, $Maghrib, 
     *                               $Isha, $Sunset, $Midnight, $Imsak]
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     * @author Hamid Zarrabi-Zadeh <zarrabi@scs.carleton.ca>
     * @source http://praytimes.org/calculation
     */
    public function getPrayTime2()
    {
        // Calculate Julian date
        if ($this->month <= 2) {
            $this->year  -= 1;
            $this->month += 12;
        }
        $A = floor($this->year / 100);
        $B = 2 - $A + floor($A / 4);

        $jd = floor(365.25 * ($this->year + 4716)) + floor(30.6001 * ($this->month + 1)) + $this->day + $B - 1524.5;
        
        // The following algorithm from U.S. Naval Observatory computes the 
        // Sun's angular coordinates to an accuracy of about 1 arcminute within 
        // two centuries of 2000. 
        $d = $jd - 2451545.0;  // jd is the given Julian date 

        // The following algorithm from U.S. Naval Observatory computes the Sun's 
        // angular coordinates to an accuracy of about 1 arcminute within two 
        // centuries of 2000
        // http://aa.usno.navy.mil/faq/docs/SunApprox.php
        $g = 357.529 + 0.98560028 * $d;
        $g = $g - 360 * floor($g / 360);
        if ($g < 0) {
            $g += 360;
        }
        
        $q = 280.459 + 0.98564736 * $d;
        $q = $q - 360 * floor($q / 360);
        if ($q < 0) {
            $q += 360;
        }
        
        $L = $q + 1.915 * sin(deg2rad($g)) + 0.020 * sin(deg2rad(2 * $g));
        $L = $L - 360 * floor($L / 360);
        if ($L < 0) {
            $L += 360;
        }

        $R = 1.00014 - 0.01671 * cos(deg2rad($g)) - 0.00014 * cos(deg2rad(2 * $g));
        $e = 23.439 - 0.00000036 * $d;
        $RA = rad2deg(atan2(cos(deg2rad($e))* sin(deg2rad($L)), cos(deg2rad($L))))/ 15;

        // The declination of the Sun is the angle between the rays of the sun and 
        // the plane of the earth equator. The declination of the Sun changes 
        // continuously throughout the year. This is a consequence of the Earth's 
        // tilt, i.e. the difference in its rotational and revolutionary axes. 
        $D = rad2deg(asin(sin(deg2rad($e))* sin(deg2rad($L))));  // declination of the Sun
        
        // The equation of time is the difference between time as read from a sundial 
        // and a clock. It results from an apparent irregular movement of the Sun 
        // caused by a combination of the obliquity of the Earth's rotation axis 
        // and the eccentricity of its orbit. The sundial can be ahead (fast) by 
        // as much as 16 min 33 s (around November 3) or fall behind by as much as 
        // 14 min 6 s (around February 12), as shown in the following graph:
        // http://en.wikipedia.org/wiki/File:Equation_of_time.png 
        $EqT = $q/15 - $RA;  // equation of time
        if ($EqT > 12) {
            $EqT -= 24;
        }
        
        // Dhuhr
        // When the Sun begins to decline after reaching its highest point in the sky
        $Dhuhr = 12 + $this->zone - $this->long/15 - $EqT;
        
        // Sunrise & Sunset 
        // If the observer's location is higher than the surrounding terrain, we 
        // can consider this elevation into consideration by increasing the above 
        // constant 0.833 by 0.0347 × sqrt(h), where h is the observer's height 
        // in meters. 
        $alpha = 0.833 + 0.0347 * sqrt($h);
        $n     = -1 * sin(deg2rad($alpha)) - sin(deg2rad($this->lat)) * sin(deg2rad($D));
        $d     = cos(deg2rad($this->lat)) * cos(deg2rad($D));

        $Sunrise = $Dhuhr - (1/15) * rad2deg(acos($n / $d));
        $Sunset  = $Dhuhr + (1/15) * rad2deg(acos($n / $d));
        
        // Fajr & Isha
        // Imsak 	The time to stop eating Sahur (for fasting), slightly before Fajr.
        // Fajr 	When the sky begins to lighten (dawn).
        // Isha 	 The time at which darkness falls and there is no scattered light in the sky. 
        $n     = -1 * sin(deg2rad(abs($this->AJ2))) - sin(deg2rad($this->lat)) * sin(deg2rad($D));
        $Fajr  = $Dhuhr - (1/15) * rad2deg(acos($n / $d));
        $Imsak = $Fajr - (10/60);
        
        $n    = -1 * sin(deg2rad(abs($this->AG2))) - sin(deg2rad($this->lat)) * sin(deg2rad($D));
        $Isha = $Dhuhr + (1/15) * rad2deg(acos($n / $d));
        
        // Asr
        // The following formula computes the time difference between the mid-day 
        // and the time at which the object's shadow equals t times the length of 
        // the object itself plus the length of that object's shadow at noon
        if ($this->school == 'Shafi') {
            $n = sin(atan(1/(1 + tan(deg2rad($this->lat - $D))))) - sin(deg2rad($this->lat)) * sin(deg2rad($D));
        } else {
            $n = sin(atan(1/(2 + tan(deg2rad($this->lat - $D))))) - sin(deg2rad($this->lat)) * sin(deg2rad($D));
        }
        $Asr = $Dhuhr + (1/15) * rad2deg(acos($n / $d));
        
        // Maghrib
        // In the Sunni's point of view, the time for Maghrib prayer begins once 
        // the Sun has completely set beneath the horizon, that is, Maghrib = Sunset 
        // (some calculators suggest 1 to 3 minutes after Sunset for precaution)
        $MaghribSunni = $Sunset + 2/60;
        
        // In the Shia's view, however, the dominant opinion is that as long as 
        // the redness in the eastern sky appearing after sunset has not passed 
        // overhead, Maghrib prayer should not be performed.
        $n           = -1 * sin(deg2rad(4)) - sin(deg2rad($this->lat)) * sin(deg2rad($D));
        $MaghribShia = $Dhuhr + (1/15) * rad2deg(acos($n / $d));
        
        if ($this->view == 'Sunni') {
            $Maghrib = $MaghribSunni;
        } else {
            $Maghrib = $MaghribShia;
        }

        // Midnight
        // Midnight is generally calculated as the mean time from Sunset to Sunrise
        $MidnightSunni = $Sunset + 0.5 * ($Sunrise - $Sunset);
        if ($MidnightSunni > 12) {
            $MidnightSunni = $MidnightSunni - 12;
        }
        
        // In Shia point of view, the juridical midnight (the ending time for 
        // performing Isha prayer) is the mean time from Sunset to Fajr
        $MidnightShia = 0.5 * ($Fajr - $Sunset);
        if ($MidnightShia > 12) {
            $MidnightShia = $MidnightShia - 12;
        }
        
        if ($this->view == 'Sunni') {
            $Midnight = $MidnightSunni;
        } else {
            $Midnight = $MidnightShia;
        }

        $times = array($Fajr, $Sunrise, $Dhuhr, $Asr, $Maghrib, $Isha, $Sunset, $Midnight, $Imsak);
        
        // Convert number after the decimal point into minutes 
        foreach ($times as $index => $time) {
            $hours   = floor($time);
            $minutes = round(($time - $hours) * 60);
            
            if ($minutes < 10) {
                $minutes = "0$minutes";
            }
            
            $times[$index] = "$hours:$minutes";
        }
        
        return $times;
    }

    /**
     * Determine Qibla direction using basic spherical trigonometric formula 
     *                        
     * @return float Qibla Direction (from the north direction) in degrees
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     * @author S. Kamal Abdali <k.abdali@acm.org>
     * @source http://www.patriot.net/users/abdali/ftp/qibla.pdf
     */
    public function getQibla () 
    {
        // The geographical coordinates of the Ka'ba
        $K_latitude  = deg2rad(21.423333);
        $K_longitude = deg2rad(39.823333);
        
        $latitude  = deg2rad($this->lat);
        $longitude = deg2rad($this->long);
        
        $numerator   = sin($K_longitude - $longitude);
        $denominator = (cos($latitude) * tan($K_latitude)) -
                       (sin($latitude) * cos($K_longitude - $longitude));

        $q = atan($numerator / $denominator);
        $q = rad2deg($q);
        
        if ($this->lat > 21.423333) {
            $q += 180;
        }
        
        return $q;
    }
    
    /**
     * Convert coordinates presented in degrees, minutes and seconds 
     * (i.e. 12°34'56"S formula) into usual float number in degree unit scale 
     * (i.e. -12.5822 value)
     *      
     * @param string $value Coordinate presented in degrees, minutes and seconds
     *                      (i.e. 12°34'56"S formula)     
     *      
     * @return float Equivalent float number in degree unit scale
     *               (i.e. -12.5822 value)     
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public function coordinate2deg ($value) 
    {
        $pattern = "/(\d{1,2})°((\d{1,2})')?((\d{1,2})\")?([NSEW])/i";
        
        preg_match($pattern, $value, $matches);
        
        $degree = $matches[1] + ($matches[3] / 60) + ($matches[5] /3600);
        
        $direction = strtoupper($matches[6]);
        
        if ($direction == 'S' || $direction == 'W') {
            $degree = -1 * $degree;
        }
        
        return $degree;
    }
}
