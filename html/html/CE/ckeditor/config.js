/*
Copyright (c) 2003-2011, CKSource - Frederico Knabben. All rights reserved.
For licensing, see LICENSE.html or http://ckeditor.com/license
*/

CKEDITOR.editorConfig = function( config )
{
	// Define changes to default configuration here. For example:
	// config.language = 'fr';
	// config.uiColor = '#AADC6E';
	config.width = 760; //Questa dimensione non è male per la toolbar
	//config.height = '25em';
	//config.resize_minHeight = 400;
	//config.resize_maxHeight = 400;
	config.enterMode = CKEDITOR.ENTER_BR;
	//config.entities = false;
	config.resize_enabled = false;
	
	config.toolbar = 'MyToolbar';
	
	/*
    config.toolbar_MyToolbar =
    [
        ['NewPage','Preview'],
        ['Cut','Copy','Paste','PasteText','PasteFromWord','-','Scayt'],
        ['Undo','Redo','-','Find','Replace','-','SelectAll','RemoveFormat'],
        ['Image','Flash','Table','HorizontalRule','Smiley','SpecialChar','PageBreak'],
        '/',
        ['Styles','Format'],
        ['Bold','Italic','Strike'],
        ['NumberedList','BulletedList','-','Outdent','Indent','Blockquote'],
        ['Link','Unlink','Anchor'],
        ['Maximize','-','About']
    ];
	*/
	
    config.toolbar_MyToolbar =
        [
            ['Source','Preview'],
            ['Cut','Copy','Paste','PasteText','PasteFromWord','-','Scayt'],
            ['Undo','Redo','-','Find','Replace','-','SelectAll','RemoveFormat'],
            ['Image','Table','HorizontalRule','SpecialChar','PageBreak'],
            ['Outdent','Indent','Blockquote'],
            '/',
            ['Styles','Format','Font','FontSize'],
            ['Bold','Italic','Underline','Strike','-','Subscript','Superscript'],
            ['NumberedList','BulletedList'],
            ['TextColor','BGColor'],
            //['ShowBlocks','-','About']
            ['About']
        ];

};
