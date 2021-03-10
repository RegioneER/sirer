<!DOCTYPE html>
<html lang="it-IT">
	<@includeLayout layout._template.header />

	<body>
		<#--div  class="bannerBar">
			<img src="/logo_gemelli.png" style="height: 70px; width: 200px;">
			<img class="pull-right" src="/logo_ctms.png" style="height: 70px; width: 200px;">
		</div-->
		
		<@includeLayout layout.topbar />
		
		<div class="main-container" id="main-container">
		 <script type="text/javascript">
		 try{ace.settings.check('main-container' , 'fixed')}catch(e){}
		 </script>
		 <div class="main-container-inner">

		 <@includeLayout layout.sidenav />

			<div class="main-content">
				<@includeLayout layout.breadcrumbs />

				<div class="page-content">
					<#if page.no_header!false ><!--if no such thing as "no-header", then print header-->
					<div class="page-header">
						<h1>${page.title!} <#list page.description as description ><small><i class="icon-double-angle-right"></i> ${page.description}</small></#list></h1>
					</div><!--/.page-header-->
					</#if>

					<div class="row">
					 <div class="col-xs-12">
<!-- PAGE CONTENT BEGINS -->

<@includeLayout page.content  />

<!-- PAGE CONTENT ENDS -->
					 </div><!--/.col-->
					</div><!--/.row-->

				</div><!--/.page-content-->

			</div><!--/.main-content -->

			<@includeLayout layout.settings />
			
			
			
			
			
			
							<#--div class="ace-settings-container" id="ace-settings-container">
					<div class="btn btn-app btn-xs btn-warning ace-settings-btn" id="ace-settings-btn">
						<i class="icon-cog bigger-150"></i>
					</div>

					<div class="ace-settings-box" id="ace-settings-box">
						<div>
							<div class="pull-left">
								<select id="skin-colorpicker" class="hide">
									<option data-skin="default" value="#438EB9">#438EB9</option>
									<option data-skin="skin-1" value="#222A2D">#222A2D</option>
									<option data-skin="skin-2" value="#C6487E">#C6487E</option>
									<option data-skin="skin-3" value="#D0D0D0">#D0D0D0</option>
								</select>
							</div>
							<span>&nbsp; Choose Skin</span>
						</div>

						<div>
							<input type="checkbox" class="ace ace-checkbox-2" id="ace-settings-navbar" />
							<label class="lbl" for="ace-settings-navbar"> Fixed Navbar</label>
						</div>

						<div>
							<input type="checkbox" class="ace ace-checkbox-2" id="ace-settings-sidebar" />
							<label class="lbl" for="ace-settings-sidebar"> Fixed Sidebar</label>
						</div>

						<div>
							<input type="checkbox" class="ace ace-checkbox-2" id="ace-settings-breadcrumbs" />
							<label class="lbl" for="ace-settings-breadcrumbs"> Fixed Breadcrumbs</label>
						</div>

						<div>
							<input type="checkbox" class="ace ace-checkbox-2" id="ace-settings-rtl" />
							<label class="lbl" for="ace-settings-rtl"> Right To Left (rtl)</label>
						</div>

						<div>
							<input type="checkbox" class="ace ace-checkbox-2" id="ace-settings-add-container" />
							<label class="lbl" for="ace-settings-add-container">
								Inside
								<b>.container</b>
							</label>
						</div>
					</div>
				</div--><!-- /#ace-settings-container -->
			
			
		 </div><!--/.main-container-inner-->

		 <a href="#" id="btn-scroll-up" class="btn-scroll-up btn btn-sm btn-inverse">
			<i class="icon-double-angle-up icon-only bigger-110"></i>
		 </a>
		</div><!--/.main-container-->

		<@includeLayout layout._template.footer />

		<!--div align="center">
			<hr>
			<img src="/logo_cineca.jpg" style="width: 50px; height: 54px;">
		</div-->
	<script>
		//LUIGI: faccio in modo che le tendine siano più larghe ma restino responsive
		$("[id*='select']").css('width', '400px');
		$("[id*='select']").css('max-width', '100%');

		    var Base64 = {
                // private property
                _keyStr : "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=",

                // public method for encoding
                encode : function (input) {
                    var output = "";
                    var chr1, chr2, chr3, enc1, enc2, enc3, enc4;
                    var i = 0;

                    input = Base64._utf8_encode(input);

                    while (i < input.length) {

                        chr1 = input.charCodeAt(i++);
                        chr2 = input.charCodeAt(i++);
                        chr3 = input.charCodeAt(i++);

                        enc1 = chr1 >> 2;
                        enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);
                        enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);
                        enc4 = chr3 & 63;

                        if (isNaN(chr2)) {
                            enc3 = enc4 = 64;
                        } else if (isNaN(chr3)) {
                            enc4 = 64;
                        }

                        output = output +
                        Base64._keyStr.charAt(enc1) + Base64._keyStr.charAt(enc2) +
                        Base64._keyStr.charAt(enc3) + Base64._keyStr.charAt(enc4);

                    }

                    return output;
                },

                // public method for decoding
                decode : function (input) {
                    var output = "";
                    var chr1, chr2, chr3;
                    var enc1, enc2, enc3, enc4;
                    var i = 0;

                    input = input.replace(/[^A-Za-z0-9\+\/\=]/g, "");

                    while (i < input.length) {

                        enc1 = Base64._keyStr.indexOf(input.charAt(i++));
                        enc2 = Base64._keyStr.indexOf(input.charAt(i++));
                        enc3 = Base64._keyStr.indexOf(input.charAt(i++));
                        enc4 = Base64._keyStr.indexOf(input.charAt(i++));

                        chr1 = (enc1 << 2) | (enc2 >> 4);
                        chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);
                        chr3 = ((enc3 & 3) << 6) | enc4;

                        output = output + String.fromCharCode(chr1);

                        if (enc3 != 64) {
                            output = output + String.fromCharCode(chr2);
                        }
                        if (enc4 != 64) {
                            output = output + String.fromCharCode(chr3);
                        }

                    }

                    output = Base64._utf8_decode(output);

                    return output;

                },

                // private method for UTF-8 encoding
                _utf8_encode : function (string) {
                    string = string.replace(/\r\n/g,"\n");
                    var utftext = "";

                    for (var n = 0; n < string.length; n++) {

                        var c = string.charCodeAt(n);

                        if (c < 128) {
                            utftext += String.fromCharCode(c);
                        }
                        else if((c > 127) && (c < 2048)) {
                            utftext += String.fromCharCode((c >> 6) | 192);
                            utftext += String.fromCharCode((c & 63) | 128);
                        }
                        else {
                            utftext += String.fromCharCode((c >> 12) | 224);
                            utftext += String.fromCharCode(((c >> 6) & 63) | 128);
                            utftext += String.fromCharCode((c & 63) | 128);
                        }

                    }

                    return utftext;
                },

                // private method for UTF-8 decoding
                _utf8_decode : function (utftext) {
                    var string = "";
                    var i = 0;
                    var c = c2 = c3 = 0;

                    while ( i < utftext.length ) {

                        c = utftext.charCodeAt(i);

                        if (c < 128) {
                            string += String.fromCharCode(c);
                            i++;
                        }
                        else if((c > 191) && (c < 224)) {
                            c2 = utftext.charCodeAt(i+1);
                            string += String.fromCharCode(((c & 31) << 6) | (c2 & 63));
                            i += 2;
                        }
                        else {
                            c2 = utftext.charCodeAt(i+1);
                            c3 = utftext.charCodeAt(i+2);
                            string += String.fromCharCode(((c & 15) << 12) | ((c2 & 63) << 6) | (c3 & 63));
                            i += 3;
                        }

                    }
                    return string;
                }
            }


		function btoaUTF16 (sString) {

			var aUTF16CodeUnits = new Uint16Array(sString.length);
			Array.prototype.forEach.call(aUTF16CodeUnits, function (el, idx, arr) { arr[idx] = sString.charCodeAt(idx); });
			return btoa(String.fromCharCode.apply(null, new Uint8Array(aUTF16CodeUnits.buffer)));

		}

		function atobUTF16 (sBase64) {

			var sBinaryString = atob(sBase64), aBinaryView = new Uint8Array(sBinaryString.length);
			Array.prototype.forEach.call(aBinaryView, function (el, idx, arr) { arr[idx] = sBinaryString.charCodeAt(idx); });
			return String.fromCharCode.apply(null, new Uint16Array(aBinaryView.buffer));

		}

		function b64EncodeUnicode(str) {
			// first we use encodeURIComponent to get percent-encoded UTF-8,
			// then we convert the percent encodings into raw bytes which
			// can be fed into btoa.
			return btoa(encodeURIComponent(str).replace(/%([0-9A-F]{2})/g,
					function toSolidBytes(match, p1) {
						return String.fromCharCode('0x' + p1);
					}));
		}
		function b64DecodeUnicode(str) {
			// Going backwards: from bytestream, to percent-encoding, to original string.
			return decodeURIComponent(atob(str).split('').map(function(c) {
				return '%' + ('00' + c.charCodeAt(0).toString(16)).slice(-2);
			}).join(''));
		}

		function php_base64_encode (stringToEncode) {
			// eslint-disable-line camelcase
			//  discuss at: http://locutus.io/php/base64_encode/
			// original by: Tyler Akins (http://rumkin.com)
			// improved by: Bayron Guevara
			// improved by: Thunder.m
			// improved by: Kevin van Zonneveld (http://kvz.io)
			// improved by: Kevin van Zonneveld (http://kvz.io)
			// improved by: Rafał Kukawski (http://blog.kukawski.pl)
			// bugfixed by: Pellentesque Malesuada
			// improved by: Indigo744
			//   example 1: base64_encode('Kevin van Zonneveld')
			//   returns 1: 'S2V2aW4gdmFuIFpvbm5ldmVsZA=='
			//   example 2: base64_encode('a')
			//   returns 2: 'YQ=='
			//   example 3: base64_encode('✓ à la mode')
			//   returns 3: '4pyTIMOgIGxhIG1vZGU='

			// encodeUTF8string()
			// Internal function to encode properly UTF8 string
			// Adapted from Solution #1 at https://developer.mozilla.org/en-US/docs/Web/API/WindowBase64/Base64_encoding_and_decoding
			var encodeUTF8string = function (str) {
				// first we use encodeURIComponent to get percent-encoded UTF-8,
				// then we convert the percent encodings into raw bytes which
				// can be fed into the base64 encoding algorithm.
				return encodeURIComponent(str).replace(/%([0-9A-F]{2})/g,
						function toSolidBytes (match, p1) {
							return String.fromCharCode('0x' + p1)
						})
			}

			if (typeof window !== 'undefined') {
				if (typeof window.btoa !== 'undefined') {
					return window.btoa(encodeUTF8string(stringToEncode))
				}
			} else {
				return new Buffer(stringToEncode).toString('base64')
			}

			var b64 = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/='
			var o1
			var o2
			var o3
			var h1
			var h2
			var h3
			var h4
			var bits
			var i = 0
			var ac = 0
			var enc = ''
			var tmpArr = []

			if (!stringToEncode) {
				return stringToEncode
			}

			stringToEncode = encodeUTF8string(stringToEncode)

			do {
				// pack three octets into four hexets
				o1 = stringToEncode.charCodeAt(i++)
				o2 = stringToEncode.charCodeAt(i++)
				o3 = stringToEncode.charCodeAt(i++)

				bits = o1 << 16 | o2 << 8 | o3

				h1 = bits >> 18 & 0x3f
				h2 = bits >> 12 & 0x3f
				h3 = bits >> 6 & 0x3f
				h4 = bits & 0x3f

				// use hexets to index into b64, and append result to encoded string
				tmpArr[ac++] = b64.charAt(h1) + b64.charAt(h2) + b64.charAt(h3) + b64.charAt(h4)
			} while (i < stringToEncode.length)

			enc = tmpArr.join('')

			var r = stringToEncode.length % 3

			return (r ? enc.slice(0, r - 3) : enc) + '==='.slice(r || 3)
		}

		//jquery.base64.min.js
		//"use strict";jQuery.base64=(function($){var _PADCHAR="=",_ALPHA="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",_VERSION="1.0";function _getbyte64(s,i){var idx=_ALPHA.indexOf(s.charAt(i));if(idx===-1){throw"Cannot decode base64"}return idx}function _decode(s){var pads=0,i,b10,imax=s.length,x=[];s=String(s);if(imax===0){return s}if(imax%4!==0){throw"Cannot decode base64"}if(s.charAt(imax-1)===_PADCHAR){pads=1;if(s.charAt(imax-2)===_PADCHAR){pads=2}imax-=4}for(i=0;i<imax;i+=4){b10=(_getbyte64(s,i)<<18)|(_getbyte64(s,i+1)<<12)|(_getbyte64(s,i+2)<<6)|_getbyte64(s,i+3);x.push(String.fromCharCode(b10>>16,(b10>>8)&255,b10&255))}switch(pads){case 1:b10=(_getbyte64(s,i)<<18)|(_getbyte64(s,i+1)<<12)|(_getbyte64(s,i+2)<<6);x.push(String.fromCharCode(b10>>16,(b10>>8)&255));break;case 2:b10=(_getbyte64(s,i)<<18)|(_getbyte64(s,i+1)<<12);x.push(String.fromCharCode(b10>>16));break}return x.join("")}function _getbyte(s,i){var x=s.charCodeAt(i);if(x>255){throw"INVALID_CHARACTER_ERR: DOM Exception 5"}return x}function _encode(s){if(arguments.length!==1){throw"SyntaxError: exactly one argument required"}s=String(s);var i,b10,x=[],imax=s.length-s.length%3;if(s.length===0){return s}for(i=0;i<imax;i+=3){b10=(_getbyte(s,i)<<16)|(_getbyte(s,i+1)<<8)|_getbyte(s,i+2);x.push(_ALPHA.charAt(b10>>18));x.push(_ALPHA.charAt((b10>>12)&63));x.push(_ALPHA.charAt((b10>>6)&63));x.push(_ALPHA.charAt(b10&63))}switch(s.length-imax){case 1:b10=_getbyte(s,i)<<16;x.push(_ALPHA.charAt(b10>>18)+_ALPHA.charAt((b10>>12)&63)+_PADCHAR+_PADCHAR);break;case 2:b10=(_getbyte(s,i)<<16)|(_getbyte(s,i+1)<<8);x.push(_ALPHA.charAt(b10>>18)+_ALPHA.charAt((b10>>12)&63)+_ALPHA.charAt((b10>>6)&63)+_PADCHAR);break}return x.join("")}return{decode:_decode,encode:_encode,VERSION:_VERSION}}(jQuery));

	</script>
	</body>
</html>