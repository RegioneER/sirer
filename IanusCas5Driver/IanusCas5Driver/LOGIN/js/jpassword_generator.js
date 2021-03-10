(function($){

        $.fn.extend({
			generatePassword: function(options)
			{
				var defaults = {
					length	: 25,
				};
				
				options = $.extend(defaults, options);
				var password = "";
				var ascii = [[48, 57],[64,90],[97,122]];
				for ( var i = 0; i < options.length; i++)
				{
					var floor = Math.floor(Math.random() * ascii.length);
					password += String.fromCharCode(Math.floor(Math.random() * (ascii[floor][1] - ascii[floor][0])) + ascii[floor][0]);
				}
			
				return password;
			}
		});
		
})(jQuery);
