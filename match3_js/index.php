<?php
$onFacebook = false;
?>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, height=device-height, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
<title>Candy Rain</title>

  <script type="text/javascript">
<![CDATA[
try {
	if (!window.CloudFlare) {
		var CloudFlare = [{
				verbose : 0,
				p : 0,
				byc : 0,
				owlid : "cf",
				bag2 : 1,
				mirage2 : 0,
				oracle : 0,
				paths : {
					cloudflare : "/balloonbang/facebook3/"
				},
				atok : "d7d37a0a650542d0b3973c89545ece79",
				petok : "74b4bb85365c33874e8d4d3af7262be2492aa54d-1460690806-1800",
				zone : "gamessumo.com",
				rocket : "m",
				apps : {},
				sha2test : 0
			}
		];
		document.write('<script type="text/javascript" src="//ajax.cloudflare.com/cdn-cgi/nexp/dok3v=e982913d31/cloudflare.min.js"><' + '\/script>');
	}
} catch (e) {};
]]>
</script>

<script type = "text/javascript" >
    <?php 
    if($onFacebook){
        echo "if (document.referrer.search('facebook.com') > 0) {
            }
            else {
            	window.location.href = 'https://apps.facebook.com/balloonfly';
            }";
    }
    ?>
    
</script>

<script src="//ads.lfstmedia.com/getad?site=271064" type="text/javascript"></script>
<style>
* {
      padding: 0;
      margin: 0;
      font-family: Arial;
    }
  body,html 
{
  height: 100%; 
  width: 100%;
  margin: 0;
  background-color: #4AA4C2;
}

.loader {
  width: 100%;
  height: 100px;
  position: absolute;
  text-align:center;
  margin-top: 250px;
    display: block !important;
}

#viewporter {
  margin: 0 auto;
  width: 100%; 
  height: 100%;
  margin-top: 0px;
}
.fc-box {
    position: relative;
    background: #fff;
    width: 728px;
    margin: 0 auto;
    overflow: hidden;
}
    .top-ad {
    position: absolute;
    top: 0px;
    left: 0;
    right: 0;
    width: 728px;
    height: 0px;
    margin: 0 auto;
}

.bottom-ad {
    width: 728px;
    margin: 0 auto;
}

.fb-box-like {
    margin: 0 auto;
    margin-top: 5px;
    width: 355px;
}
.description p, .description a {
    color: #fff;
    text-align: center;
    font-weight: bold;
    font-size: 15px;
}

.cbutton {
    height: 16px;
    display: inline;
    outline: none;
    cursor: pointer;
    text-align: center;
    text-decoration: none;
    font: 14px/100%;
    font-weight: bold;
    padding: .3em 1em .3em;
    -webkit-border-radius: 0.2em;
    -moz-border-radius: 0.2em;
    border-radius: 0.2em;
    -webkit-box-shadow: 0 1px 2px rgba(0, 0, 0, .2);
    -moz-box-shadow: 0 1px 2px rgba(0, 0, 0, .2);
    box-shadow: 0 1px 2px rgba(0, 0, 0, .2);
        background: white;
    font-family: "lucida grande", tahoma, verdana, arial, sans-serif;
    font-size: 11px;
    color: #333;
    margin: 0;
    padding: 0;
    text-align: left;
    direction: ltr;
    unicode-bidi: embed;
}

.white {
        background: #4c69ba;
    background: linear-gradient(#4c69ba, #3b55a0);
    border: none;
    border-radius: 2px;
    color: #fff;
    cursor: pointer;
    font-weight: bold;
    height: 20px;
    line-height: 20px;
    padding: 0;
    text-shadow: 0 -1px 0 #354c8c;
    white-space: nowrap;
    padding: 4px 11px;
}

.white:hover {
   background: #5b7bd5;
    background: linear-gradient(#5b7bd5, #4864b1);
    border-color: #5874c3 #4961a8 #41599f;
    box-shadow: inset 0 0 1px #607fd6;
}
.cbutton:hover {
    text-decoration: none;
}

.container-popup {
    position: relative;
    position: fixed;
    top: 0;
    right: 0;
    bottom: 0;
    left: 0;
    background: rgba(0,0,0,.8);
    z-index: 1099;
}

.popup {
    width: 300px;
    height: 250px;
    background: #fff;
    position: absolute;
    top: 0;
    right: 0;
    bottom: 0;
    left: 0;
    margin: auto;
    z-index: 1100;
}
#close {
    right: 0;
    position: absolute;
    top: -18px;
    cursor: pointer;
    z-index: 1999;
    /*
    position: absolute;
    right: 0;
    padding: 3px;
    border-radius: 50px;
    cursor: pointer;
    z-index: 9999;
    */
}

.fb-top {
  position: absolute;
  top: 100px;
  left: 0;
  right: 0;
  width: 120px;
  margin: 0 auto;
}

.loading-box {
   left: 0;
    position: absolute;
    top: -17px;
    cursor: pointer;
    z-index: 1999;
    color: #fff;
    font-size: 12px;
}
</style>
<script type="text/javascript">
    window.gameLangs = ['en'];
    window.gameJS = ['softgames_game.js'];
    window.gameOnLoadScript = "init();";
</script>
<script type="text/javascript" src="softgames-1.1.js"></script>
<script type="text/javascript" src="sg.hooks.js"></script>

</head>
<body>
<div class="top-ad">
<script type="text/javascript">
    <![CDATA[
        LSM_Slot({
            adkey: '7cf',
            ad_size: '728x90',
            slot: 'slot132422'
        });
    ]]>
</script>
</div>

     <div id="viewporter">
        <canvas id="canvas" width="700" height="900"></canvas><div id="loader"></div>
    </div>

    <div class="container-popup"></div>
    <div class="popup">
            <img id="close" src="close-button.png" />

             <script type="text/javascript">
                <![CDATA[
                    LSM_Slot({
                        adkey: '76c',
                        ad_size: '300x250',
                        slot: 'slot133383'
                    });
                ]]>
            </script>
    </div>
  </div>

  <div class="bottom-ad">
    <script type="text/javascript">
        <![CDATA[
            LSM_Slot({
                adkey: 'd3d',
                ad_size: '728x90',
                slot: 'slot133425'
            });
        ]]>
    </script>
  </div>
  
<?php 
if($onFacebook){
echo "<script>
    window.fbAsyncInit = function() {
        FB.init({
            appId      : '222876548077145',
            xfbml      : true,
            version    : 'v2.6'
        });
    };

    function sendRequests() {
        FB.ui({
            method: 'apprequests',
            message: 'Play this awesome Facebook game.',
            data: ''
        }, function(response) {
    
        });
    }

  (function(d, s, id){
     var js, fjs = d.getElementsByTagName(s)[0];
     if (d.getElementById(id)) {return;}
     js = d.createElement(s); js.id = id;
     js.src = '//connect.facebook.net/en_US/sdk.js';
     fjs.parentNode.insertBefore(js, fjs);
   }(document, 'script', 'facebook-jssdk'));
</script>
";

}


?>  
 
<script src="https://code.jquery.com/jquery-2.1.1.min.js" 
    integrity="sha256-h0cGsrExGgcZtSZ/fRz4AwV+Nn6Urh/3v3jFRQ0w9dQ="
    crossorigin="anonymous"></script>
 
<script type="text/javascript">
  $("#close").click(function(){
                $('.popup').hide(); $('.container-popup').hide();
              });	
$('.popup').hide(); $('.container-popup').hide();              	  
</script>
    </body>
</html>
