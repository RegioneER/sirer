var validation_messages="";
var validation_confirmation_messages="";

(function() {
	rivets.binders.input = {
		publishes : true,
		routine : rivets.binders.value.routine,
		bind : function(el) {
			return $(el).bind('input.rivets', this.publish);
		},
		unbind : function(el) {
			return $(el).unbind('input.rivets');
		}
	};

	rivets.configure({
		prefix : "rv",
		adapter : {
			subscribe : function(obj, keypath, callback) {
				callback.wrapped = function(m, v) {
					return callback(v);
				};
				return obj.on('change:' + keypath, callback.wrapped);
			},
			unsubscribe : function(obj, keypath, callback) {
				return obj.off('change:' + keypath, callback.wrapped);
			},
			read : function(obj, keypath) {
				if (keypath === "cid") {
					return obj.cid;
				}
				return obj.get(keypath);
			},
			publish : function(obj, keypath, value) {
				if (obj.cid) {
					return obj.set(keypath, value);
				} else {
					return obj[keypath] = value;
				}
			}
		}
	});

}).call(this);

(function() {
	var BuilderView, EditFieldView, Formbuilder, FormbuilderCollection, FormbuilderModel, ViewFieldView, _ref, _ref1, _ref2, _ref3, _ref4, __hasProp = {}.hasOwnProperty, __extends = function(child, parent) {
		for (var key in parent) {
			if (__hasProp.call(parent, key))
				child[key] = parent[key];
		}
		function ctor() {
			this.constructor = child;
		}


		ctor.prototype = parent.prototype;
		child.prototype = new ctor();
		child.__super__ = parent.prototype;
		return child;
	};

	FormbuilderModel = (function(_super) {
		__extends(FormbuilderModel, _super);

		function FormbuilderModel() {
			_ref = FormbuilderModel.__super__.constructor.apply(this, arguments);
			return _ref;
		}


		FormbuilderModel.prototype.sync = function() {
		};

		FormbuilderModel.prototype.indexInDOM = function() {
			var $wrapper, _this = this;
			/*$wrapper = $(".fb-field-wrapper").filter((function(_, el) {
				return $(el).data('cid') === _this.cid;
			}));*/
			$wrapper=$("#field_view_"+_this.attributes.cid);
			return $(".fb-field-wrapper").index($wrapper);
		};

		FormbuilderModel.prototype.is_input = function() {
			return Formbuilder.inputFields[this.get(Formbuilder.options.mappings.FIELD_TYPE)] != null;
		};

		return FormbuilderModel;

	})(Backbone.DeepModel);

	FormbuilderCollection = (function(_super) {
		__extends(FormbuilderCollection, _super);

		function FormbuilderCollection() {
			_ref1 = FormbuilderCollection.__super__.constructor.apply(this, arguments);
			return _ref1;
		}


		FormbuilderCollection.prototype.initialize = function() {
			return this.on('add', this.copyCidToModel);
		};

		FormbuilderCollection.prototype.model = FormbuilderModel;

		FormbuilderCollection.prototype.comparator = function(model) {
			return model.indexInDOM();
		};

		FormbuilderCollection.prototype.copyCidToModel = function(model) {
			return model.attributes.cid = model.cid;
		};

		return FormbuilderCollection;

	})(Backbone.Collection);

	ViewFieldView = (function(_super) {
		__extends(ViewFieldView, _super);

		function ViewFieldView() {
			_ref2 = ViewFieldView.__super__.constructor.apply(this, arguments);
			return _ref2;
		}


		ViewFieldView.prototype.className = "fb-field-wrapper";

		ViewFieldView.prototype.events = {
			'click .subtemplate-wrapper' : 'focusEditView',
			'click .js-duplicate' : 'duplicate',
			'click .js-clear' : 'clear'
		};

		ViewFieldView.prototype.initialize = function(options) {
			this.parentView = options.parentView;
			this.listenTo(this.model, "change", this.render);
			return this.listenTo(this.model, "destroy", this.remove);
		};

		ViewFieldView.prototype.render = function() {
			this.$el.addClass('response-field-' + this.model.get(Formbuilder.options.mappings.FIELD_TYPE)).data('cid', this.model.cid).html(Formbuilder.templates["view/base" + (!this.model.is_input() ? '_non_input' : '')]({
				rf : this.model
			}));
			this.$el.prop("id", "field_view_"+this.model.attributes.cid);
			return this;
		};

		ViewFieldView.prototype.focusEditView = function(e) {
			return this.parentView.createAndShowEditView(this.model,e);
		};

		ViewFieldView.prototype.clear = function(e) {
			var cb, x, _this = this;
			e.preventDefault();
			e.stopPropagation();
			cb = function() {
				_this.parentView.handleFormUpdate();
				return _this.model.destroy();
			};
			x = Formbuilder.options.CLEAR_FIELD_CONFIRM;
			switch (typeof x) {
				case 'string':
					if (confirm(x)) {
						return cb();
					}
					break;
				case 'function':
					return x(cb);
				default:
					return cb();
			}
		};

		ViewFieldView.prototype.duplicate = function() {
			var attrs;
			attrs = _.clone(this.model.attributes);
			delete attrs['id'];
			attrs['label'] += ' Copy';
			return this.parentView.createField(attrs, {
				position : this.model.indexInDOM() + 1
			});
		};

		return ViewFieldView;

	})(Backbone.View);

	EditFieldView = (function(_super) {
		__extends(EditFieldView, _super);

		function EditFieldView() {
			_ref3 = EditFieldView.__super__.constructor.apply(this, arguments);
			return _ref3;
		}


		EditFieldView.prototype.className = "edit-response-field";

		EditFieldView.prototype.events = {
			'click .js-add-option' : 'addOption',
			'click .js-add-rangecheck' : 'addRangeCheck',
			'click .js-remove-option' : 'removeOption',
			'click .js-remove-rangecheck' : 'removeRangeCheck',
			//'click .js-default-updated' : 'defaultUpdated',
			'click .js-default-updated' : 'forceRender',
			'click .js-default-updated_disabled' : 'forceRender',
			'input .option-label-input' : 'forceRender',
			'input .option-value-input' : 'forceRender',
			'input .option-checkvalue-input' : 'forceRender',
			//'input .input-mask-date' : 'forceRender',
			'input .option-message-input' : 'forceRender'
		};

		EditFieldView.prototype.initialize = function(options) {
			this.parentView = options.parentView;
			return this.listenTo(this.model, "destroy", this.remove);
		};

		EditFieldView.prototype.render = function() {
			this.$el.html(Formbuilder.templates["edit/base" + (!this.model.is_input() ? '_non_input' : '')]({
				rf : this.model
			}));
			rivets.bind(this.$el, {
				model : this.model
			});
			return this;
		};

		EditFieldView.prototype.remove = function() {
			this.parentView.editView =
			void 0;
			this.parentView.$el.find("[data-target=\"#addField\"]").click();
			return EditFieldView.__super__.remove.apply(this, arguments);
		};

		EditFieldView.prototype.addOption = function(e) {
			var $el, i, newOption, options;
			$el = $(e.currentTarget);
			i = this.$el.find('.option').index($el.closest('.option'));
			options = this.model.get(Formbuilder.options.mappings.VALUES) || [];
			newOption = {
				label : "",
				checked : false
			};
			if (i > -1) {
				options.splice(i + 1, 0, newOption);
			} else {
				options.push(newOption);
			}
			this.model.set(Formbuilder.options.mappings.VALUES, options);
			this.model.trigger("change:" + Formbuilder.options.mappings.VALUES);
			return this.forceRender(e);
		};

		EditFieldView.prototype.removeOption = function(e) {
			var $el, index, options;
			$el = $(e.currentTarget);
			index = this.$el.find(".js-remove-option").index($el);
			options = this.model.get(Formbuilder.options.mappings.VALUES);
			options.splice(index, 1);
			this.model.set(Formbuilder.options.mappings.VALUES, options);
			this.model.trigger("change:" + Formbuilder.options.mappings.VALUES);
			return this.forceRender(e);
		};
		
		
		
		EditFieldView.prototype.addRangeCheck = function(e) {
			var $el, i, newOption, options;
			$el = $(e.currentTarget);
			i = this.$el.find('.option').index($el.closest('.option'));
			options = this.model.get(Formbuilder.options.mappings.RANGECHECKS) || [];
			newOption = {
				comparator : "",
				checkValue : "",
				level : "",
				message : ""
			};
			if (i > -1) {
				options.splice(i + 1, 0, newOption);
			} else {
				options.push(newOption);
			}
			this.model.set(Formbuilder.options.mappings.RANGECHECKS, options);
			this.model.trigger("change:" + Formbuilder.options.mappings.RANGECHECKS);
			//$('.input-mask-date').mask('9999-99-99');
			populateFieldRangeCheckValue($("select[data-rv-value='option:checkValue']"),this.model.attributes.rangecheck);
			return this.forceRender(e);
		};

		EditFieldView.prototype.removeRangeCheck = function(e) {
			var $el, index, options;
			$el = $(e.currentTarget);
			index = this.$el.find(".js-remove-rangecheck").index($el);
			options = this.model.get(Formbuilder.options.mappings.RANGECHECKS);
			options.splice(index, 1);
			if(options.length==0){
				options=undefined;
			}
			this.model.set(Formbuilder.options.mappings.RANGECHECKS, options);
			this.model.trigger("change:" + Formbuilder.options.mappings.RANGECHECKS);
			return this.forceRender(e);
		};

		/*EditFieldView.prototype.defaultUpdated = function(e) {
			var $el;
			$el = $(e.currentTarget);
			if (this.model.get(Formbuilder.options.mappings.FIELD_TYPE) !== 'checkboxes') {
				this.$el.find(".js-default-updated").not($el).attr('checked', false).trigger('change');
				//this.model.trigger("change");
			}
			return this.forceRender();
		};*/

		EditFieldView.prototype.forceRender = function(e) {
			//inserisco qua dentro il codice della funzione defaultUpdated perchè c'era un bug sul check del radio in visualizzazione
			var $el;
			$el = $(e.currentTarget);
			if (this.model.get(Formbuilder.options.mappings.FIELD_TYPE) === 'radio') {
					var is_checked=$el.is(':checked');
					//per tutte le altre opzioni che non siano quella appena cliccata
					var my_class=$el.prop("class");
					if($el.prop("class")=="js-default-updated"){
						this.$el.find(".js-default-updated").not($el).each(function(){
							var this_class=$(this).prop("class");
							if(this_class!="js-default-updated _disabled" && is_checked && $(this).is(':checked')){
								$(this).prop('checked', false);
							}
						});
						
					}
					else if($el.prop("class")=="js-default-updated_disabled"){
						this.$el.find(".js-default-updated").each(function(){
							if(!is_checked){
								$(this).propr("disabled",false);
							}
						});
						
					}
					//aggiorno tutte le relative "viste" delle radio nel pannello a dx
						this.$el.find(".js-default-updated").trigger('change');
						this.$el.find(".js-default-updated_disabled").trigger('change');
			}
			return this.model.trigger('change');
		};

		return EditFieldView;

	})(Backbone.View);

	BuilderView = (function(_super) {
		__extends(BuilderView, _super);

		function BuilderView() {
			_ref4 = BuilderView.__super__.constructor.apply(this, arguments);
			return _ref4;
		}


		BuilderView.prototype.SUBVIEWS = [];

		BuilderView.prototype.events = {
			'click .js-save-form' : 'saveForm',
			'click .fb-tabs a' : 'showTab',
			'click .fb-add-field-types a' : 'addField',
			'mouseover .fb-add-field-types' : 'lockLeftWrapper',
			'mouseout .fb-add-field-types' : 'unlockLeftWrapper',
			//'click .panel-default' : 'unlockLeftWrapper'
		};

		BuilderView.prototype.initialize = function(options) {
			var selector;
			selector = options.selector, this.formBuilder = options.formBuilder, this.bootstrapData = options.bootstrapData;
			if (selector != null) {
				this.setElement($(selector));
			}
			this.collection = new FormbuilderCollection;
			this.collection.bind('add', this.addOne, this);
			this.collection.bind('reset', this.reset, this);
			this.collection.bind('change', this.handleFormUpdate, this);
			this.collection.bind('destroy add reset', this.hideShowNoResponseFields, this);
			this.collection.bind('destroy', this.ensureEditViewScrolled, this);
			this.render();
			this.collection.reset(this.bootstrapData);
			return this.bindSaveEvent();
		};

		BuilderView.prototype.bindSaveEvent = function() {
			var _this = this;
			this.formSaved = true;
			this.saveFormButton = this.$el.find(".js-save-form");
			this.saveFormButton.attr('disabled', true).text(Formbuilder.options.dict.ALL_CHANGES_SAVED);
			if (!!Formbuilder.options.AUTOSAVE) {
				setInterval(function() {
					return _this.saveForm.call(_this);
				}, 5000);
			}
			return $(window).bind('beforeunload', function() {
				if (_this.formSaved) {
					return
					void 0;
				} else {
					return Formbuilder.options.dict.UNSAVED_CHANGES;
				}
			});
		};

		BuilderView.prototype.reset = function() {
			this.$responseFields.html('');
			return this.addAll();
		};

		BuilderView.prototype.render = function() {
			var subview, _i, _len, _ref5;
			this.$el.html(Formbuilder.templates['page']());
			this.$fbLeft = this.$el.find('.fb-left');
			this.$fbSaveWrapper = this.$el.find('.fb-save-wrapper');
			this.$responseFields = this.$el.find('.fb-response-fields');
			this.bindWindowScrollEvent();
			this.hideShowNoResponseFields();
			_ref5 = this.SUBVIEWS;
			for ( _i = 0, _len = _ref5.length; _i < _len; _i++) {
				subview = _ref5[_i];
				new subview({
					parentView : this
				}).render();
			}
			return this;
		};

		BuilderView.prototype.bindWindowScrollEvent = function() {
			var _this = this;
			return $(window).on('scroll', function() {
				var maxMargin, newMargin;
				newMargin = Math.max(0, $(window).scrollTop() - _this.$el.offset().top);
				maxMargin = _this.$responseFields.height();
				if (_this.$fbLeft.data('locked') === true) {
					return (_this.$fbLeft.css({
						'margin-top' :  Math.min(_this.fbLeftTopMargin, newMargin)
					}) && _this.$fbSaveWrapper.css({
						'border-top' : Math.min(maxMargin, newMargin)+"px solid #fff"
					}));
				}
				_this.fbLeftTopMargin=Math.min(maxMargin, newMargin);
				return (_this.$fbLeft.css({
					'margin-top' : _this.fbLeftTopMargin
				}) && _this.$fbSaveWrapper.css({
					'border-top' : _this.fbLeftTopMargin+"px solid #fff"
				}));
			});
		};

		BuilderView.prototype.showTab = function(e) {
			var $el, first_model, target;
			$el = $(e.currentTarget);
			target = $el.data('target');
			$el.closest('li').addClass('active').siblings('li').removeClass('active');
			$(target).addClass('active').siblings('.fb-tab-pane').removeClass('active');
			if (target !== '#editField') {
				this.unlockLeftWrapper();
			}
			if (target === '#editField' && !this.editView && ( first_model = this.collection.models[0])) {
				return this.createAndShowEditView(first_model);
			}
			if (target === '#formAttributes' &&  ( first_model = this.collection.models[0])) {
				//alert(target);
				$('.response-field-form').find('.subtemplate-wrapper').click();
				return false;
			}
		};

		BuilderView.prototype.addOne = function(responseField, _, options) {
			var $replacePosition, view;
			view = new ViewFieldView({
				model : responseField,
				parentView : this
			});
			if (options.$replaceEl != null) {
				return options.$replaceEl.replaceWith(view.render().el);
			} else if ((options.position == null) || options.position === -1) {
				return this.$responseFields.append(view.render().el);
			} else if (options.position === 0) {
				return this.$responseFields.prepend(view.render().el);
			} else if (($replacePosition = this.$responseFields.find(".fb-field-wrapper").eq(options.position))[0]) {
				return $replacePosition.before(view.render().el);
			} else {
				return this.$responseFields.append(view.render().el);
			}
		};

		BuilderView.prototype.setSortable = function() {
			var _this = this;
			if (this.$responseFields.hasClass('ui-sortable')) {
				this.$responseFields.sortable('destroy');
			}
			this.$responseFields.sortable({
				forcePlaceholderSize : true,
				placeholder : 'sortable-placeholder',
				stop : function(e, ui) {
					var rf;
					if (ui.item.data('field-type')) {
						rf = _this.collection.create(Formbuilder.helpers.defaultFieldAttrs(ui.item.data('field-type')), {
							$replaceEl : ui.item
						});
						_this.createAndShowEditView(rf);
					}
					_this.handleFormUpdate();
					return true;
				},
				update : function(e, ui) {
					if (!ui.item.data('field-type')) {
						return _this.ensureEditViewScrolled();
					}
				}
			});
			return this.setDraggable();
		};

		BuilderView.prototype.setDraggable = function() {
			var $addFieldButtons, _this = this;
			$addFieldButtons = this.$el.find("[data-field-type]");
			return $addFieldButtons.draggable({
				connectToSortable : this.$responseFields,
				helper : function() {
					var $helper;
					$helper = $("<div class='response-field-draggable-helper' />");
					$helper.css({
						width : _this.$responseFields.width(),
						height : '80px'
					});
					return $helper;
				}
			});
		};

		BuilderView.prototype.addAll = function() {
			this.collection.each(this.addOne, this);
			return this.setSortable();
		};

		BuilderView.prototype.hideShowNoResponseFields = function() {
			return this.$el.find(".fb-no-response-fields")[this.collection.length > 0 ? 'hide' : 'show']();
		};

		BuilderView.prototype.addField = function(e) {
			var field_type;
			field_type = $(e.currentTarget).data('field-type');
			return this.createField(Formbuilder.helpers.defaultFieldAttrs(field_type));
		};

		BuilderView.prototype.createField = function(attrs, options) {
			var rf;
			rf = this.collection.create(attrs, options);
			this.createAndShowEditView(rf);
			return this.handleFormUpdate();
		};

		BuilderView.prototype.createAndShowEditView = function(model,e) {
			var $newEditEl, $responseFieldEl;
			var my_el=this.$el;
			if(e!==undefined){
				$responseFieldEl=e.currentTarget;
				$responseFieldEl=$($responseFieldEl).parent();
			}
			else{
				$responseFieldEl = this.$el.find(".fb-field-wrapper").filter(function() {
					return $(this).data('cid') === model.cid;
				});
			}
			$responseFieldEl.addClass('editing').siblings('.fb-field-wrapper').removeClass('editing');
			if (this.editView) {
				if (this.editView.model.cid === model.cid) {
					if($responseFieldEl.hasClass('response-field-form')){
						this.$el.find(".fb-tabs a[data-target=\"#formAttributes\"]").click();
						this.scrollLeftWrapper($responseFieldEl);
					}
					else{
					this.$el.find(".fb-tabs a[data-target=\"#editField\"]").click();
					this.scrollLeftWrapper($responseFieldEl);
					}
					return;
				}
				this.editView.remove();
			}
			this.editView = new EditFieldView({
				model : model,
				parentView : this
			});
			$newEditEl = this.editView.render().$el;
			if($responseFieldEl.hasClass('response-field-form')){
				this.$el.find(".fb-edit-form-wrapper").html($newEditEl);
				this.$el.find(".fb-tabs a[data-target=\"#formAttributes\"]").click();
				if(model.attributes.form_options['main_field']!==undefined){
					model.attributes.form_options['main_field']=model.attributes.form_options['main_field'].toUpperCase().trim().replace(/ /g, "").replace(/\W/g, "");
					$('input[data-rv-input="model.form_options.main_field"]').val(model.attributes.form_options['main_field']);
				}
				if(model.attributes.form_options['table_sub']!==undefined){
					model.attributes.form_options['table_sub']=model.attributes.form_options['table_sub'].toUpperCase().trim().replace(/ /g, "").replace(/\W/g, "");
					$('input[data-rv-input="model.form_options.table_sub"]').val(model.attributes.form_options['table_sub']);
				}
				this.scrollLeftWrapper($responseFieldEl);
			}
			else{
				this.$el.find(".fb-edit-field-wrapper").html($newEditEl);
				this.$el.find(".fb-tabs a[data-target=\"#editField\"]").click();
				var current_field=JSON.stringify(model.attributes);
				//alert(current_field);
				$("#current_field").val(current_field);
				
				
				if(model.attributes.field_options['var']!==undefined){
					model.attributes.field_options['var']=model.attributes.field_options['var'].toUpperCase().trim().replace(/ /g, "").replace(/\W/g, "");
					$('input[data-rv-input="model.field_options.var"]').val(model.attributes.field_options['var']);
				}
				if(model.attributes.value!=undefined){
					$(model.attributes.value).each(function(key,_model){
		
						if($($("#collapseRadioValues").children(".option")[key]).find('input[data-rv-input="option:value"]').val()!==undefined){
							$($("#collapseRadioValues").children(".option")[key]).find('input[data-rv-input="option:value"]').val($($("#collapseRadioValues").children(".option")[key]).find('input[data-rv-input="option:value"]').val().toUpperCase().trim().replace(/ /g, "").replace(/\W/g, "").replace($("#study_prefix").val()+"_",""));
							_model.value=$($("#collapseRadioValues").children(".option")[key]).find('input[data-rv-input="option:value"]').val();
						}
					});
				}
				
				
				if(model.attributes.field_type=='textarea'){ //disabilito la scelta della option "number" da var_type se sono una textarea
					$('select[data-rv-value="model.field_options.var_type"]').children("option[value='number']").prop('disabled', true);
				}
				
				
				$('select[data-rv-value="model.field_options.var_type"]').bind('change',function (){ //disabilito o abilito il var_size a seconda che il var_type sia TEXT o NUMBER
					if($(this).val()=='text')
					{
						$('input[data-rv-input="model.field_options.var_size"]').prop('disabled',false);
					}
					else{
						$('input[data-rv-input="model.field_options.var_size"]').prop('disabled',true);
					}
				});
				if($('select[data-rv-value="model.field_options.var_type"]').val()!='text'){
					$('input[data-rv-input="model.field_options.var_size"]').prop('disabled',true);
				}
				
				if($('select[data-rv-value="model.field_options.txt_align"]').val()==null){ //imposto per default gli allineamenti di field e label
					$('select[data-rv-value="model.field_options.txt_align"]').val('right');
				}
				$('select[data-rv-value="model.field_options.txt_align"]').trigger("change");
				if($('select[data-rv-value="model.field_options.field_align"]').val()==null){
					$('select[data-rv-value="model.field_options.field_align"]').val('left');
				}
				if($("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.RANGECHECKS_OPERATOR )) == null ? '' : __t) +"']").length && ($("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.RANGECHECKS_OPERATOR )) == null ? '' : __t) +"']").val()===undefined || $("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.RANGECHECKS_OPERATOR )) == null ? '' : __t) +"']").val()===null || $("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.RANGECHECKS_OPERATOR )) == null ? '' : __t) +"']").val()=="")){
					$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.RANGECHECKS_OPERATOR )) == null ? '' : __t) +"']").val("AND").change();
					fb.mainView.editView.model.attributes.field_options.rangecheck_operator="AND";
					model.attributes.field_options['rangecheck_operator']="AND";
				}
				populateFieldRangeCheckValue($("select[data-rv-value='option:checkValue']"),fb.mainView.editView.model.attributes.rangecheck);
				$('select[data-rv-value="model.field_options.field_align"]').trigger("change");
				populateFieldCondition($("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.CONDITION )) == null ? '' : __t) +"']"),model.attributes.field_options.condition);
				populateFieldCompilaCondition("input[id='model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VAR )) == null ? '' : __t) + "']","input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VAR )) == null ? '' : __t) + "']");
				populateFieldBYTB($("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.BYTB )) == null ? '' : __t) +"']"),model.attributes.field_options.bytb);
				populateFieldBYTBCODE($("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.BYTBCODE )) == null ? '' : __t) +"']"),model.attributes.field_options.bytb,model.attributes.field_options.bytbcode);
				populateFieldBYTBCODE($("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.BYTBDECODE )) == null ? '' : __t) +"']"),model.attributes.field_options.bytb,model.attributes.field_options.bytbdecode);
				
				this.scrollLeftWrapper($responseFieldEl);
				
			}
			
			if($('input[data-rv-input=\'model.form_options.main_field\']').val()!=""){ //se è form-attributes e sono in una main simulo click  
				$('input[data-rv-checked=\'model.form_options.is_main\']').trigger('click');
				$('input[data-rv-input=\'model.form_options.main_field\']').prop('disabled',false);
				$('input[data-rv-input=\'model.form_options.main_field_value\']').prop('disabled',false);
				$('input[data-rv-input=\'model.form_options.table_sub\']').prop('disabled',false);
				$('input[data-rv-input=\'model.form_options.field_tb_show\']').prop('disabled',true);
				$('input[data-rv-input=\'model.form_options.tb_header\']').prop('disabled',true);
				
			}
			else{
				$('input[data-rv-checked=\'model.form_options.is_main\']').trigger('click').trigger('click');
				$('input[data-rv-input=\'model.form_options.main_field\']').prop('disabled',true);
				$('input[data-rv-input=\'model.form_options.main_field_value\']').prop('disabled',true);
				$('input[data-rv-input=\'model.form_options.table_sub\']').prop('disabled',true);
				$('input[data-rv-input=\'model.form_options.field_tb_show\']').prop('disabled',false);
				$('input[data-rv-input=\'model.form_options.tb_header\']').prop('disabled',false);
			}
			$('input[data-rv-checked=\'model.form_options.is_main\']').bind('click',function (){Formbuilder.templates['MainChecked']();}); //associo funzione al click
			
			
			
			if(model.attributes.field_type=='form'){
				populateLinkTo($("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.LINK_TO )) == null ? '' : __t) +"']"),model.attributes.form_options.link_to);
				populateLinkTo($("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.LINK_TO_SEND )) == null ? '' : __t) +"']"),model.attributes.form_options.link_to_send);
				populateFToCall($("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.F_TO_CALL )) == null ? '' : __t) +"']"),model.attributes.form_options.f_to_call);
				Formbuilder.validators['validate/form'](model.attributes,true);//chiamo validatore per visualizzare eventuali errori negli attributi
			}
			else {
				Formbuilder.validators['validate/'+model.attributes.field_type](model.attributes,true);//chiamo validatore per visualizzare eventuali errori negli attributi
			}
			return this;
		};

		BuilderView.prototype.ensureEditViewScrolled = function() {
			if (!this.editView) {
				return;
			}
			return this.scrollLeftWrapper($(".fb-field-wrapper.editing"));
		};

		BuilderView.prototype.scrollLeftWrapper = function($responseFieldEl) {
			var _this = this;
			this.unlockLeftWrapper();
			if (!$responseFieldEl[0]) {
				return;
			}
			return this.scrollWindowTo((this.$el.offset().top + $responseFieldEl.offset().top) - this.$responseFields.offset().top, 200, function() {
				return _this.lockLeftWrapper();
			});
		};
		
		BuilderView.prototype.scrollWindowTo = function(pos, duration, cb) {
		  if (duration == null) {
		    duration = 0;
		  }
		  if (pos === $(window).scrollTop()) {
		    $(window).trigger('scroll');
		    if (typeof cb === "function") {
		      cb();
		    }
		    return;
		  }
		  return $('html, body').animate({
		    scrollTop: pos
		  }, duration, function() {
		    return typeof cb === "function" ? cb() : void 0;
		  });
		};

		BuilderView.prototype.lockLeftWrapper = function() {
			return this.$fbLeft.data('locked', true);
		};

		BuilderView.prototype.unlockLeftWrapper = function() {
			return this.$fbLeft.data('locked', false);
		};

		BuilderView.prototype.handleFormUpdate = function() {
			if (this.updatingBatch) {
				return;
			}
			this.formSaved = false;
			return this.saveFormButton.removeAttr('disabled').text(Formbuilder.options.dict.SAVE_FORM);
		};

		BuilderView.prototype.saveForm = function(e) {
			var payload;
			if (this.formSaved) {
				return;
			}
			// this.collection.sort();
			// payload = JSON.stringify({
				// fields : this.collection.toJSON()
			// });
// 			
			/**
			 * VALIDAZIONE FIELD PER FIELD
			 */
			var _this=this;
			var all_is_valid=true;
			$(this.collection.toJSON()).each(function(key,model){
				//alert (model);
				if(model.field_type=='form'){
					is_valid=Formbuilder.validators['validate/form'](model,false);
					if(all_is_valid){
						all_is_valid=is_valid; //se ho qualcosa non valida, continuo con il controllo di tutto il resto ma non posso farmi sovrascrivere che ho trovato un elemento non valido!
					}
				}
				else if(model.field_type=='text'||model.field_type=='textbox'||model.field_type=='checkbox'||model.field_type=='date_cal'||model.field_type=='ora'||model.field_type=='textarea'||model.field_type=='radio'||model.field_type=='select'|| ( model.field_type=='hidden' && model.field_options.pk!='yes')){
					 is_valid=Formbuilder.validators['validate/'+model.field_type](model,false);
					 if(all_is_valid){
						all_is_valid=is_valid; //se ho qualcosa non valida, continuo con il controllo di tutto il resto ma non posso farmi sovrascrivere che ho trovato un elemento non valido!
					}
				}
			});
			if(all_is_valid){
				this.collection.sort();
				payload = JSON.stringify({
					fields : this.collection.toJSON()
				});
				if (Formbuilder.options.HTTP_ENDPOINT) {
					this.doAjaxSave(payload);
				}
				all_is_valid=this.formBuilder.trigger('save', payload);
			}
			else{
				bootbox.alert({
						message : "<b>Some validation errors are present in the form, please check the fields highlighted in red</b>",
						title : 'Validating Form',
						className : "structLoader",
						});	
			}
			return all_is_valid;
		};

		BuilderView.prototype.doAjaxSave = function(payload) {
			var _this = this;
			return $.ajax({
				url : Formbuilder.options.HTTP_ENDPOINT,
				type : Formbuilder.options.HTTP_METHOD,
				data : payload,
				contentType : "application/json",
				success : function(data) {
					var datum, _i, _len, _ref5;
					_this.updatingBatch = true;
					for ( _i = 0, _len = data.length; _i < _len; _i++) {
						datum = data[_i];
						if (( _ref5 = _this.collection.get(datum.cid)) != null) {
							_ref5.set({
								id : datum.id
							});
						}
						_this.collection.trigger('sync');
					}
					return _this.updatingBatch =
					void 0;
				}
			});
		};

		return BuilderView;

	})(Backbone.View);

	Formbuilder = (function() {
		Formbuilder.helpers = {
			defaultFieldAttrs : function(field_type) {
				var attrs, _base;
				attrs = {};
				attrs[Formbuilder.options.mappings.LABEL] = 'Untitled';
				attrs[Formbuilder.options.mappings.FIELD_TYPE] = field_type;
				attrs[Formbuilder.options.mappings.REQUIRED] = true;
				attrs['field_options'] = {};
				return ( typeof ( _base = Formbuilder.fields[field_type]).defaultAttributes === "function" ? _base.defaultAttributes(attrs) :
				void 0) || attrs;
			},
			simple_format : function(x) {
				return x != null ? x.replace(/\n/g, '<br />') :
				void 0;
			}
		};

		Formbuilder.options = {
			BUTTON_CLASS : 'btn btn-info',
			HTTP_ENDPOINT : '',
			HTTP_METHOD : 'POST',
			AUTOSAVE : false,
			CLEAR_FIELD_CONFIRM : true,
			mappings : {
				SIZE : 'field_options.size',
				UNITS : 'field_options.units',
				LABEL : 'label',
				FIELD_TYPE : 'field_type',
				REQUIRED : 'required',
				ADMIN_ONLY : 'admin_only',
				OPTIONS : 'field_options.options',
				DESCRIPTION : 'field_options.description',
				INCLUDE_OTHER : 'field_options.include_other_option',
				INCLUDE_BLANK : 'field_options.include_blank_option',
				INTEGER_ONLY : 'field_options.integer_only',
				MIN : 'field_options.min',
				MAX : 'field_options.max',
				MINLENGTH : 'field_options.minlength',
				MAXLENGTH : 'field_options.maxlength',
				LENGTH_UNITS : 'field_options.min_max_length_units',
				
				/**
				 *PERSONALIZZAZIONI XMR FORM BUILDER 
				 * vmazzeo dsaraceno maggio 2014
				 * START
				 */
				//ATTRIBUTI FORM
				FNAME :'form_options.fname',
				TITOLO :'form_options.titolo',
				TABLE :'form_options.table',
				LINK_TO :'form_options.link_to',
				LINK_TO_SEND :'form_options.link_to_send',
				COLS :'form_options.cols',
				LOAD :'form_options.load',
				JS_FUNCTION :'form_options.js_function',
				JS_ONSAVE :'form_options.js_onsave',
				F_TO_CALL :'form_options.f_to_call',
				IS_MAIN : 'form_options.is_main',
				MAIN_FIELD :'form_options.main_field',
				MAIN_FIELD_VALUE :'form_options.main_field_value',
				FIELD_TB_SHOW :'form_options.field_tb_show',
				TB_HEADER :'form_options.tb_header',
				TABLE_SUB :'form_options.table_sub',
				ENABLE : 'enable',
				VISITE_EXAMS : 'visite_exams',
				SEND_BUTTON:'send',
				SAVE_BUTTON:'save',
				CANCEL_BUTTON:'cancel',
				SHOW_SEND_BUTTON:'show_send',
				SHOW_SAVE_BUTTON:'show_save',
				SHOW_CANCEL_BUTTON:'show_cancel',
				//ATTRIBUTI FIELD
				TXT_VALUE : 'field_options.txt_value',
				UPPER : 'field_options.upper',
				VAR : 'field_options.var',
				VAR_TYPE : 'field_options.var_type',
				PK : 'field_options.pk',
				VAR_SIZE : 'field_options.var_size',
				BYTB : 'field_options.bytb',
				BYTBNOPREFIX : 'field_options.bytbnoprefix',
				BYTBCODE : 'field_options.bytbcode',
				BYTBDECODE : 'field_options.bytbdecode',
				BYTBWHERE : 'field_options.bytbwhere',
				BYTBORDERBY : 'field_options.bytborderby',
				BYVAR : 'field_options.byvar',
				SEC_PROGR : 'field_options.sec_progr',
				TB : 'field_options.tb',
				FIELD_COLS : 'field_options.cols',
				COLSPAN : 'field_options.colspan',
				SUBTBCOL : 'field_options.subtbcol',
				MULTIREC : 'field_options.multirec',
				SIZE : 'field_options.size',
				MIN : 'field_options.min',
				CRYPTO : 'field_options.crypto',
				ONCLICK : 'field_options.onclick',
				CONDITION : 'field_options.condition',
				CONDITION_VALUE : 'field_options.condition_value',
				COMPILA_CONDITION_VAR : 'field_options.compila_condition_var',
				COMPILA_CONDITION_VALUE : 'field_options.compila_condition_value',
				COMPILA_CONDITION_OP : 'field_options.compila_condition_op',
				COMPILA : 'field_options.compila',
				HIDE : 'field_options.hide',
				FM_CODE : 'field_options.fm_code',
				SEND : 'field_options.send',
				SAVE : 'field_options.save',
				DESCRIPTION : 'field_options.description',
				ON_BLUR : 'field_options.on_blur',
				ON_ACTION : 'field_options.on_action',
				ACTION_TYPE : 'field_options.action_type',
				TCOLS : 'field_options.tcols',
				ROWS : 'field_options.rows',
				SHOW_VIS : 'field_options.show_vis',
				SHOW_SELECTED : 'field_options.show_selected',
				FIELD_ALIGN : 'field_options.field_align',
				TXT_ALIGN : 'field_options.txt_align',
				LABEL_JS : 'field_options.label_js',
				DEF : 'field_options.def',
				DISABLED : 'field_options.disabled_always',
				MAIN : 'field_options.main',
				HIDE_THIS : 'field_options.hide_this',
				HIDEVIS : 'field_options.hidevis',
				VALUE : 'value',
				VALUES : 'value',
				RANGECHECKS: 'rangecheck',
				RANGECHECKS_OPERATOR: 'field_options.rangecheck_operator',
				DISABLED_VAL: 'field_options.disabled_val',
				EMAIL: 'field_options.email',
				GROUP_SAVE: 'field_options.group_save',
				GROUP_SEND: 'field_options.group_send',
				GROUP: 'field_options.group',
				VALUE_GROUP: 'field_options.value_group',
				NDAY: 'field_options.nday',
				FORMAT: 'field_options.format',
				DCONT: 'field_options.dcont',
				DSPEC: 'field_options.dspec',
				NNDAYVALUE: 'field_options.nndayvalue',
				NNMONTHVALUE: 'field_options.nnmonthvalue',
				LIFECYCLE_ACTIVITY:'field_options.lifecycle_activity',
				/**
				 *PERSONALIZZAZIONI XMR FORM BUILDER 
				 * vmazzeo dsaraceno maggio 2014
				 * END
				 */
				
			},
			dict : {
				ALL_CHANGES_SAVED : 'All changes saved',
				SAVE_FORM : 'Save form',
				UNSAVED_CHANGES : 'You have unsaved changes. If you leave this page, you will lose those changes!',
				EDIT_FORM_XML : 'Edit xml file',
				UPDATE_DB_TABLE : 'Update DB Table',
				DROP_DB_TABLE : 'Drop DB Table'
			}
		};

		Formbuilder.fields = {};

		Formbuilder.inputFields = {};

		Formbuilder.nonInputFields = {};

		Formbuilder.registerField = function(name, opts) {
			var x, _i, _len, _ref5;
			_ref5 = ['view', 'edit'];
			for ( _i = 0, _len = _ref5.length; _i < _len; _i++) {
				x = _ref5[_i];
				opts[x] = _.template(opts[x]);
			}
			opts.field_type = name;
			Formbuilder.fields[name] = opts;
			if (opts.type === 'non_input') {
				return Formbuilder.nonInputFields[name] = opts;
			} else {
				return Formbuilder.inputFields[name] = opts;
			}
		};

		function Formbuilder(opts) {
			var args;
			if (opts == null) {
				opts = {};
			}
			_.extend(this, Backbone.Events);
			args = _.extend(opts, {
				formBuilder : this
			});
			this.mainView = new BuilderView(args);
		}

		return Formbuilder;

	})();

	window.Formbuilder = Formbuilder;

	if ( typeof module !== "undefined" && module !== null) {
		module.exports = Formbuilder;
	} else {
		window.Formbuilder = Formbuilder;
	}

}).call(this);

/*(function() {
	Formbuilder.registerField('section_break', {
		order : 0,
		type : 'non_input',
		view : "<label class='section-name'><%= rf.get(Formbuilder.options.mappings.LABEL) %></label>\n<p><%= rf.get(Formbuilder.options.mappings.DESCRIPTION) %></p>",
		edit : "<div class='fb-edit-section-header'>Label</div>\n<input type='text' data-rv-input='model.<%= Formbuilder.options.mappings.LABEL %>' />\n<textarea data-rv-input='model.<%= Formbuilder.options.mappings.DESCRIPTION %>'\n  placeholder='Add a longer description to this field'></textarea>",
		addButton : "<span class='symbol'><span class='fa fa-minus'></span></span> Section Break"
	});

}).call(this);*/

(function() {
	Formbuilder.registerField('form', {
		order : 1,
		type : 'non_input',
		view : "<div style='background-color:#EEEEEE;padding:3px'>FORM ATTRIBUTES - click to edit form attributes on the panel on the left</div>",
		edit : 	"<div class=\"panel-group\" id=\"accordion\"> " +
				"<%= Formbuilder.templates['edit/form_name']() %>\n" +
				"<%= Formbuilder.templates['edit/form_title']() %>\n" +
				"<%= Formbuilder.templates['edit/form_table']() %>\n" +
				"<%= Formbuilder.templates['edit/form_f_to_calls']() %>" +
				"<%= Formbuilder.templates['edit/form_cols']() %>" +
				"<%= Formbuilder.templates['edit/form_links']() %>" +
				"<%= Formbuilder.templates['edit/form_js_functions']() %>" +
				"<%= Formbuilder.templates['edit/form_buttons']() %>"+
				"<%= Formbuilder.templates['edit/form_main_sub']() %>"+
				"<%= Formbuilder.templates['edit/enable_list']() %>\n" +
				//"<%= Formbuilder.templates['edit/lifecycle_activity']() %>\n" +
				"</div>",
		addButton : "",
		//validator:"<%=  Formbuilder.validators['edit/form_name']()%>\n",
		// defaultAttributes: function(attrs) {
		// attrs.field_options.options = [
		// {
		// label: "",
		// checked: false
		// }, {
		// label: "",
		// checked: false
		// }
		// ];
		// return attrs;
		// }
	});

}).call(this);



// (function() {
// Formbuilder.registerField('website', {
// order: 35,
// view: "<input type='text' placeholder='http://' />",
// edit: "",
// addButton: "<span class=\"symbol\"><span class=\"fa fa-link\"></span></span> Website"
// });
//
// }).call(this);

this["Formbuilder"] = this["Formbuilder"] || {};
this["Formbuilder"]["templates"] = this["Formbuilder"]["templates"] || {};
this["Formbuilder"]["validators"] = this["Formbuilder"]["validators"] || {};
this["Formbuilder"]["utils"] = this["Formbuilder"]["utils"] || {};
this["Formbuilder"]["utils"]["oracle_reserved_words"]= new Array("ACCESS","ADD","ALL","ALTER","AND","ANY","AS","ASC","AUDIT","BETWEEN","BY","CHAR","CHECK","CLUSTER","COLUMN","COMMENT","COMPRESS","CONNECT","CREATE","CURRENT","DATE","DECIMAL","DEFAULT","DELETE","DESC","DISTINCT","DROP","ELSE","EXCLUSIVE","EXISTS","FILE","FLOAT","FOR","FROM","GRANT","GROUP","HAVING","IDENTIFIED","IMMEDIATE","IN","INCREMENT","INDEX","INITIAL","INSERT","INTEGER","INTERSECT","INTO","IS","LEVEL","LIKE","LOCK","LONG","MAXEXTENTS","MINUS","MLSLABEL","MODE","MODIFY","NOAUDIT","NOCOMPRESS","NOT","NOWAIT","NULL","NUMBER","OF","OFFLINE","ON","ONLINE","OPTION","OR","ORDER","PCTFREE","PRIOR","PRIVILEGES","PUBLIC","RAW","RENAME","RESOURCE","REVOKE","ROW","ROWID","ROWNUM","ROWS","SELECT","SESSION","SET","SHARE","SIZE","SMALLINT","START","SUCCESSFUL","SYNONYM","SYSDATE","TABLE","THEN","TO","TRIGGER","UID","UNION","UNIQUE","UPDATE","USER","VALIDATE","VALUES","VARCHAR","VARCHAR2","VIEW","WHENEVER","WHERE","WITH");
this["Formbuilder"]["templates"]["edit/base"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += (( __t = ( Formbuilder.templates['edit/base_header']() )) == null ? '' : __t) + '\n' + (( __t = ( Formbuilder.templates['edit/common']() )) == null ? '' : __t) + '\n' + (( __t = ( Formbuilder.fields[rf.get(Formbuilder.options.mappings.FIELD_TYPE)].edit({
				rf : rf
			}) )) == null ? '' : __t) + '\n';

	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/base_header"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += '<div class=\'fb-field-label\'>\n  <span data-rv-text="model.' + (( __t = (Formbuilder.options.mappings.LABEL )) == null ? '' : __t) + '"></span>\n  <code class=\'field-type\' data-rv-text=\'model.' + (( __t = (Formbuilder.options.mappings.FIELD_TYPE )) == null ? '' : __t) + '\'></code>\n  <span class=\'fa fa-arrow-right pull-right\'></span>\n</div><br/><div class=\'fb-clear\'></div>\n';

	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/base_non_input"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += (( __t = ( Formbuilder.templates['edit/base_header']() )) == null ? '' : __t) + '\n' + (( __t = ( Formbuilder.fields[rf.get(Formbuilder.options.mappings.FIELD_TYPE)].edit({
				rf : rf
			}) )) == null ? '' : __t) + '\n';

	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/checkboxes"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		//vmazzeo gestirò l'obbligatorietà tramite attributi save e send
//		__p += '<label>\n  <input type=\'checkbox\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.REQUIRED )) == null ? '' : __t) + '\' />\n  Required\n</label>\n<label>\n  <input type=\'checkbox\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.ADMIN_ONLY )) == null ? '' : __t) + '\' />\n  Admin only\n</label>';

	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/common"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		
		__p += 	' 	<div class=\'fb-clear\'></div>\n'+
				'	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseFieldLabel" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Field label'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseFieldLabel" class="panel-collapse collapse" style="height: 0px;">'+
				'		<div class=\'fb-label-description\'>\n    ' + (( __t = ( Formbuilder.templates['edit/label_description']() )) == null ? '' : __t) + '\n  </div>\n' +
				//'		<div class=\'fb-common-checkboxes\'>\n    ' + (( __t = ( Formbuilder.templates['edit/checkboxes']() )) == null ? '' : __t) + '\n  </div>\n'+
				' 		<div class=\'fb-clear\'></div>\n'+
				'	</div>'+
				'	</div>'+
				'	</div>';
				
				// '<div class=\'fb-edit-section-header\'>Field label</div>\n\n'+
				// '	<div class=\'fb-common-wrapper\'>\n'+  
				// '		<div class=\'fb-label-description\'>\n    ' + (( __t = ( Formbuilder.templates['edit/label_description']() )) == null ? '' : __t) + '\n  </div>\n' +
				// '		<div class=\'fb-common-checkboxes\'>\n    ' + (( __t = ( Formbuilder.templates['edit/checkboxes']() )) == null ? '' : __t) + '\n  </div>\n'+
				// ' 		<div class=\'fb-clear\'></div>\n'+
				// '</div>\n';
	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/integer_only"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += '<div class=\'fb-edit-section-header\'>Integer only</div>\n<label>\n  <input type=\'checkbox\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.INTEGER_ONLY )) == null ? '' : __t) + '\' />\n  Only accept integers\n</label>\n';

	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/label_description"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += '<input type=\'text\' data-rv-input=\'model.' + (( __t = (Formbuilder.options.mappings.LABEL )) == null ? '' : __t) + '\' />\n ';
	//vmazzeo al momento description nei campi non ci serve
	//	__p += '<textarea data-rv-input=\'model.' + (( __t = (Formbuilder.options.mappings.DESCRIPTION )) == null ? '' : __t) + '\'\n  placeholder=\'Add a longer description to this field\'></textarea>';

	}
	return __p;
};



this["Formbuilder"]["templates"]["edit/min_max_length"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += '<div class=\'fb-edit-section-header\'>Length Limit</div>\n\nMin\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.MINLENGTH )) == null ? '' : __t) + '" style="width: 30px" />\n\n&nbsp;&nbsp;\n\nMax\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.MAXLENGTH )) == null ? '' : __t) + '" style="width: 30px" />\n\n&nbsp;&nbsp;\n\n<select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.LENGTH_UNITS )) == null ? '' : __t) + '" style="width: auto;">\n  <option value="characters">characters</option>\n  <option value="words">words</option>\n</select>\n';

	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/options"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape, __j = Array.prototype.join;
	function print() {
		__p += __j.call(arguments, '');
	}

	with (obj) {
		__p += '<div class=\'fb-edit-section-header\'>Options</div>\n\n';
		if ( typeof includeBlank !== 'undefined') { 
			__p += '\n  <label>\n    <input type=\'checkbox\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.INCLUDE_BLANK )) == null ? '' : __t) + '\' />\n    Include blank\n  </label>\n';
		} ;
		__p += '\n\n<div class=\'option\' data-rv-each-option=\'model.' + (( __t = (Formbuilder.options.mappings.VALUES )) == null ? '' : __t) + '\'>\n  <input type="checkbox" class=\'js-default-updated\' data-rv-checked="option:checked" />\n  <input type="text" data-rv-input="option:label" class=\'option-label-input\' />\n  <a class="js-add-option ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Add Option"><i class=\'fa fa-plus-circle\'></i></a>\n  <a class="js-remove-option ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Remove Option"><i class=\'fa fa-minus-circle\'></i></a>\n</div>\n\n';
		if ( typeof includeOther !== 'undefined') { ;
			__p += '\n  <label>\n    <input type=\'checkbox\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.INCLUDE_OTHER )) == null ? '' : __t) + '\' />\n    Include "other"\n  </label>\n';
		} ;
		__p += '\n\n<div class=\'fb-bottom-add\'>\n  <a class="js-add-option ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '">Add option</a>\n</div>\n';

	}
	return __p;
};
/**
 *PERSONALIZZAZIONI XMR FORM BUILDER 
 * vmazzeo dsaraceno maggio 2014
 * START
*/
//EDIT ATTRIBUTI FIELDS
this["Formbuilder"]["templates"]["edit/select_values"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape, __j = Array.prototype.join;
	function print() {
		__p += __j.call(arguments, '');
	}

	with (obj) {
		//__p += '<div class=\'fb-edit-section-header\'></div>\n\n';
		
		__p += 	'	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseRadioValues" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Options'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseRadioValues" class="panel-collapse collapse" style="height: 0px;">';
		if ( typeof includeBlank !== 'undefined') { 
			__p += '\n<div style="float:left">Include blank</div><div style="float:right"><input type=\'checkbox\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.INCLUDE_BLANK )) == null ? '' : __t) + '\' /></div>\n'+
				   '<div style="clear:both"></div>';
		} ;
		__p +=	'		<div style="float:left">Show only the selected option<br/><em>when the form is closed</em></div><div style="float:right"><label><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.SHOW_SELECTED)) == null ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.SHOW_SELECTED)) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.SHOW_SELECTED )) == null ? '' : __t) + '\' /></label></div>' +
				'		<div style="clear:both"></div>'+
			 	'		<div class=\'option\' data-rv-each-option=\'model.' + (( __t = (Formbuilder.options.mappings.VALUES )) == null ? '' : __t) + '\'>\n '+
			    '			<div class="fb-field-wrapper"><div class="subtemplate-wrapper">'+
			    '				<div style="float:left">Label</div><div style="float:right"><input type="text" data-rv-input="option:label" class=\'option-label-input\' /></div>'+
			    '				<div style="clear:both"></div>'+
			    '				<div style="float:left">Value</div><div style="float:right"><input type="text" data-rv-input="option:value" class=\'option-value-input\' /></div>\n'+
			    '				<div style="clear:both"><br/></div>'+
			    '				<div class=\'actions-wrapper\'>'+
			    '					<a class="js-duplicate js-add-option ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Add Option"><i class=\'fa fa-plus-circle\'></i></a>\n'+
			    '					<a class="js-clear js-remove-option ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Remove Option"><i class=\'fa fa-minus-circle\'></i></a>\n'+
			    '				</div>'+
			    '			</div></div>'+
			    '		</div>\n\n';
			   
		if ( typeof includeOther !== 'undefined') { ;
			__p += '\n  <label>\n    <input type=\'checkbox\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.INCLUDE_OTHER )) == null ? '' : __t) + '\' />\n    Include "other"\n  </label>\n';
		} ;
		__p += '\n\n<div class=\'fb-bottom-add\'>\n  <a class="js-add-option ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '">Add option</a>\n</div>\n';

	}
		__p += '	</div>'+
			   '	</div>'+	
			   '	</div>';
	return __p;
};

this["Formbuilder"]["templates"]["edit/checkbox_values"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape, __j = Array.prototype.join;
	function print() {
		__p += __j.call(arguments, '');
	}

	with (obj) {
		//__p += '<div class=\'fb-edit-section-header\'></div>\n\n';
		
		__p += 	'	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseRadioValues" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Options'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseRadioValues" class="panel-collapse collapse" style="height: 0px;">';
		if ( typeof includeBlank !== 'undefined') { 
			__p += '\n<div style="float:left">Include blank</div><div style="float:right"><input type=\'checkbox\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.INCLUDE_BLANK )) == null ? '' : __t) + '\' /></div>\n'+
				   '<div style="clear:both"></div>';
		} ;
		__p +=	'		<div style="float:left">Options per row</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.SUBTBCOL )) == null ? '' : __t) + '" /></div>' +
				'		<div style="clear:both"></div>';
		__p +=	'		<div style="float:left">Group</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.GROUP )) == null ? '' : __t) + '" /></div>'+
				'		<div style="float:left">Value group</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.VALUE_GROUP )) == null ? '' : __t) + '" /></div>'+
				'		<div style="clear:both"></div>'+
			 	'		<div class=\'option\' data-rv-each-option=\'model.' + (( __t = (Formbuilder.options.mappings.VALUES )) == null ? '' : __t) + '\'>\n '+
			    '			<div class="fb-field-wrapper"><div class="subtemplate-wrapper">'+
			    '				<div style="float:left">Label</div><div style="float:right"><input type="text" data-rv-input="option:label" class=\'option-label-input\' /></div>'+
			    '				<div style="clear:both"></div>'+
			    '				<div style="float:left">Value</div><div style="float:right"><input type="text" data-rv-input="option:value" class=\'option-value-input\' /></div>\n'+
			    '				<div style="clear:both"><br/></div>'+
			    '				<div class=\'actions-wrapper\'>'+
			    '					<a class="js-duplicate js-add-option ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Add Option"><i class=\'fa fa-plus-circle\'></i></a>\n'+
			    '					<a class="js-clear js-remove-option ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Remove Option"><i class=\'fa fa-minus-circle\'></i></a>\n'+
			    '				</div>'+
			    '			</div></div>'+
			    '		</div>\n\n';
			   
		if ( typeof includeOther !== 'undefined') { ;
			__p += '\n  <label>\n    <input type=\'checkbox\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.INCLUDE_OTHER )) == null ? '' : __t) + '\' />\n    Include "other"\n  </label>\n';
		} ;
		__p += '\n\n<div class=\'fb-bottom-add\'>\n  <a class="js-add-option ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '">Add option</a>\n</div>\n';

	}
		__p += '	</div>'+
			   '	</div>'+	
			   '	</div>';
	return __p;
};

this["Formbuilder"]["templates"]["edit/allowed_values"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseMinMax" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Range Checks'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseMinMax" class="panel-collapse collapse" style="height: 0px;">';
		__p += 	'		<div style="float:left">Logical Operator<br/>between checks</div><div style="float:right"><select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.RANGECHECKS_OPERATOR )) == null ? '' : __t) + '">\n  <option value="AND" selected="selected">AND</option>\n  <option value="OR">OR</option>\n\n</select></div>'+
		'				<div style="clear:both"><br/></div>'+
				'		<div class=\'option\' data-rv-each-option=\'model.' + (( __t = (Formbuilder.options.mappings.RANGECHECKS )) == null ? '' : __t) + '\'>\n '+
			   	'			<div class="fb-field-wrapper"><div class="subtemplate-wrapper">'+
			   	'				<div style="float:left">Comparator</div><div style="float:right"><select data-rv-value="option:comparator" onchange="fb.mainView.handleFormUpdate();" ><option value="LT">less than (LT)</option><option value="LE">less than or equal to (LE)</option><option value="GT">greater than (GT)</option><option value="GE">greater than or equal to (GE)</option><option value="EQ">equal to (EQ)</option><option value="NE">not equal to (NE)</option></select></div>'+
			   	'				<div style="clear:both"><br/></div>'+
			   	'				<div style="float:left">Check value</div><div style="float:right"><select data-rv-value="option:checkValue" class=\'option-checkvalue-input\' ><option></option></select></div>'+
			   	'				<div style="clear:both"><br/></div>'+
			   	'				<div style="float:left"></div><div style="float:right"><input type="text" data-rv-input="option:checkValue" class=\'option-checkvalue-input\' /></div>'+
			   	'				<div style="clear:both"><br/></div>'+
			   	'				<div style="float:left">Level</div><div style="float:right"><select data-rv-value="option:level" onchange="fb.mainView.handleFormUpdate();" ><option value="Hard">Blocker</option><option value="Soft">Warning</option></select></div>'+
			   	'				<div style="clear:both"><br/></div>'+
			   	'				<div style="float:left">Message</div><div style="float:right"><input type="text" data-rv-input="option:message" class=\'option-message-input\' /></div>'+
			   	'				<div style="clear:both"><br/></div>'+
			    '				<div class=\'actions-wrapper\'>'+
			   	'					<a class="js-duplicate js-add-rangecheck ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Add Range Check"><i class=\'fa fa-plus-circle\'></i></a>\n'+
			   	'					<a class="js-clear js-remove-rangecheck ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Remove Range Check"><i class=\'fa fa-minus-circle\'></i></a>\n'+
			   	'				</div>'+
			   	'			</div></div>'+
			   	'		</div>'+
		 		'		<div class=\'fb-bottom-add\'>\n  <a class="js-add-rangecheck ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '">Add Range Check</a>\n</div>\n'+
				'	</div>'+	
				'	</div>'+
				'	</div>';

	}
	return __p;
};
this["Formbuilder"]["validators"]["validate/table_column_name_valid"] = function(obj,current,name_to_validate,is_tablename) {
	//var my_field= obj.field_options['var'];
	fields=new Array();
	$(fb.mainView.collection.models).each( function(key, model){
		fields.push(model.attributes);
	});
	//var fields=fb.mainView.collection.models;// JSON.parse($("#form_fields").val());
	
	var is_valid=true;
	var who_is=is_tablename ? "table" : "column";
	var skyp_unique_name_check=(obj.field_type=='form' && (name_to_validate==obj.form_options.main_field || name_to_validate==obj.form_options.table_sub)); //per i controlli sugli attributi main_field e table_sub non devo controllare l'univocità (banale)
	//mi prendo tutti i .var attuali
	if(name_to_validate===undefined || name_to_validate ==""){
		is_valid=false;
		
		if(current||is_tablename){
			validation_messages+="<li>The "+who_is+" name must be specified!</li>";
			//$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").css("border","1px solid red");
		}
	}
	else{
		if(!skyp_unique_name_check){
			if(!is_tablename){
				var columns = $.map( fields, function( field ) {
					if( (field.field_type!=="form") && (obj.cid!=field.cid)){
						return field.field_options.var;
					}
					return undefined;
				});
				var options=new Array(); //prendo anche tutte le option dei checkbox
					$(fields).each( function( key_field,field ) {
						if(field.field_type=="checkbox"){
							options=$.map( field.value, function( check_values ) {
								if (obj.cid!=field.cid){
					                	return check_values.value;
					            }
				           	});
				        }
						return undefined;
					});
					
				if(options.length>0){	
					$.merge(columns,options);
				}
				if(obj.field_type!=='text' && obj.field_type!=='checkbox' && $.inArray(name_to_validate,columns)>0){ //non faccio controllo sull'esistenza del nome della colonna per campi label (text) e checkbox
					is_valid=false;
					
					if(current){
						validation_messages+="<li>The "+who_is+" name is already used!</li>";
						//$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").css("border","1px solid red");
					}
				}
			}
			else{
				var current_table=$("#current_table").val();// nome tabella attualmente salvata sul file (mi serve per bypassare il mio nome attuale dalla lista delle tabelle del visite_exams)
				var tables=JSON.parse($("#structure_db_tables").val());
				jQuery.each(tables,function(table){
					if(is_valid && current_table!=table && table !== 'null' && table==name_to_validate ){
							//is_valid=false;
							validation_confirmation_messages+="<li>Table name already used! Are you sure to use an existing table in this form?</li>";
							validation_messages+="<li><span class='warning'>Table name already used! Are you sure to use an existing table in this form?</span></li>";
					}
				});
			}
		}
	
		if (name_to_validate.length > 20){
			is_valid=false;
			
			if(current||is_tablename){
				validation_messages+="<li>The "+who_is+" name can't exceed 20 characters!</li>";
				//$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").css("border","1px solid red");
			}
		}
		if ( /^\d/.test(name_to_validate)){
			is_valid=false;
			
			if(current||is_tablename){
				validation_messages+="<li>The "+who_is+" name can't start with a numeric character!</li>";
				//$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").css("border","1px solid red");
			}
		}
		if ( $.inArray(name_to_validate,Formbuilder.utils.oracle_reserved_words)>=0){
			is_valid=false;
			
			if(current||is_tablename){
				validation_messages+="<li>This "+who_is+" name can't be used because it is a reserved word!</li>";
				//$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").css("border","1px solid red");
			}
		}
	}
	
	return is_valid;
}
this["Formbuilder"]["validators"]["validate/allowed_values"] = function(obj,current) {
	var is_valid=true;
	var values_array=[]; //controllo se le option sono tutte diverse
	$(obj.rangecheck).each(function(key,model){
		if(is_valid){
			//alert(model);
			is_valid = is_valid && ( model.checkValue!="" && model.checkValue!="custom_value" ) && model.message!="" && model.level!="" ;
			if(!is_valid){
				if( model.checkValue=="" || model.checkValue=="custom_value" ){
					validation_messages+="<li>Please write the custom value in the text field</li>";
				}
				if( model.level==""){
					validation_messages+="<li>Please select the level</li>";
				}
				if( model.message==""){
					validation_messages+="<li>Please write the alert message</li>";
				}
				is_valid=is_valid && false;
				if(current){
					$($("#collapseMinMax").children(".option")[key]).css("border","1px solid red");
					$("#collapseMinMax").parent().css("border","1px solid red");
				}
			}
			else{
				if(current){
					$($("#collapseMinMax").children(".option")[key]).css("border","");
				}
			}
		}
	});
	if(is_valid&&current){
		
		$("#collapseMinMax").parent().css("border","");
	}
	return is_valid ;
};

this["Formbuilder"]["templates"]["edit/date_allowed_values"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseMinMax" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Allowed values'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseMinMax" class="panel-collapse collapse" style="height: 0px;">'+
				'		<div style="float:left">Hide the <em>day</em> input box<br/>from the field</div><div style="float:right"><input type=\'checkbox\' value=\''+(( __t = (Formbuilder.options.mappings.NDAY )) == null ? '' : __t) +'\' name=\''+(( __t = (Formbuilder.options.mappings.NDAY )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.NDAY )) == null ? '' : __t) + '\' /></div>'+
				'		<div style="clear:both"><br/></div>'+
				'		<div style="float:left">Date Format<br/><em>Oracle&reg; datetime format model</em></div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.FORMAT )) == null ? '' : __t) + '" style="width:250px"/></div>'+
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Logical Operator<br/>between checks</div><div style="float:right"><select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.RANGECHECKS_OPERATOR )) == null ? '' : __t) + '">\n  <option value="AND" selected="selected">AND</option>\n  <option value="OR">OR</option>\n\n</select></div>'+
				'		<div style="clear:both"><br/></div>';
				
				/*'		<div style="float:left">Allow to use the CONT<br/>(<em>continuous</em>) value</div><div style="float:right"><input type=\'checkbox\' value=\''+(( __t = (Formbuilder.options.mappings.DCONT )) == null ? '' : __t) +'\' name=\''+(( __t = (Formbuilder.options.mappings.DCONT )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.DCONT )) == null ? '' : __t) + '\' /></div>'+
				'		<div style="clear:both"><br/></div>'+
				'		<div style="float:left">Force the value of the <em>day</em> to NA/NK</div><div style="float:right"><input type=\'checkbox\' value=\''+(( __t = (Formbuilder.options.mappings.NNDAYVALUE )) == null ? '' : __t) +'\' name=\''+(( __t = (Formbuilder.options.mappings.NNDAYVALUE )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.NNDAYVALUE )) == null ? '' : __t) + '\' /></div>'+
				'		<div style="clear:both"><br/></div>'+
				'		<div style="float:left">Force the value of the <em>month</em> to NA/NK</div><div style="float:right"><input type=\'checkbox\' value=\''+(( __t = (Formbuilder.options.mappings.NNMONTHVALUE )) == null ? '' : __t) +'\' name=\''+(( __t = (Formbuilder.options.mappings.NNMONTHVALUE )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.NNMONTHVALUE )) == null ? '' : __t) + '\' /></div>'+
				'		<div style="clear:both"><br/></div>';*/
		__p += 	'		<div class=\'option\' data-rv-each-option=\'model.' + (( __t = (Formbuilder.options.mappings.RANGECHECKS )) == null ? '' : __t) + '\'>\n '+
			   	'			<div class="fb-field-wrapper"><div class="subtemplate-wrapper">'+
			   	'				<div style="float:left">Comparator</div><div style="float:right"><select data-rv-value="option:comparator" onchange="fb.mainView.handleFormUpdate();" ><option value="LT">less than (LT)</option><option value="LE">less than or equal to (LE)</option><option value="GT">greater than (GT)</option><option value="GE">greater than or equal to (GE)</option><option value="EQ">equal to (EQ)</option><option value="NE">not equal to (NE)</option></select></div>'+
			   	'				<div style="clear:both"><br/></div>'+
			   	'				<div style="float:left">Check value</div><div style="float:right"><select data-rv-value="option:checkValue" class=\'option-checkvalue-input\' ><option></option></select></div>'+
			   	'				<div style="clear:both"><br/></div>'+
			   	'				<div style="float:left"></div><div style="float:right"><input type="text" data-rv-input="option:checkValue" class=\'option-checkvalue-input\' /></div>'+
			   	'				<div style="clear:both"><br/></div>'+
			   	'				<div style="float:left">Level</div><div style="float:right"><select data-rv-value="option:level" onchange="fb.mainView.handleFormUpdate();" ><option value="Hard">Blocker</option><option value="Soft">Warning</option></select></div>'+
			   	'				<div style="clear:both"><br/></div>'+
			   	'				<div style="float:left">Message</div><div style="float:right"><input type="text" data-rv-input="option:message" class=\'option-message-input\' /></div>'+
			   	'				<div style="clear:both"><br/></div>'+
			    '				<div class=\'actions-wrapper\'>'+
			   	'					<a class="js-duplicate js-add-rangecheck ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Add Range Check"><i class=\'fa fa-plus-circle\'></i></a>\n'+
			   	'					<a class="js-clear js-remove-rangecheck ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Remove Range Check"><i class=\'fa fa-minus-circle\'></i></a>\n'+
			   	'				</div>'+
			   	'			</div></div>'+
			   	'		</div>'+
		 		'		<div class=\'fb-bottom-add\'>\n  <a class="js-add-rangecheck ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '">Add Range Check</a>\n</div>\n'+
				'	</div>'+	
				'	</div>'+
				'	</div>';

	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/value"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape, __j = Array.prototype.join;
	function print() {
		__p += __j.call(arguments, '');
	}

	with (obj) {
		__p +=	'	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseDefaultValue" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Default Value'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseDefaultValue" class="panel-collapse collapse" style="height: 0px;">';
		__p += 	'		<div style="float:left">Value </div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.VALUE )) == null ? '' : __t) + '" style="width: 250px" /></div>'+
			   	'		<div style="clear:both"></div>'+
			   	'		<div class=\'fb-edit-section-header\'>Default Value Conditioned</div>'+
				'		<div style="float:left">Compiled condition fields</div>'+
				'			<div style="float:right">'+
				'				<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VAR )) == null ? '' : __t) + '" id="model.' + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VAR )) == null ? '' : __t) + '" style="width: 250px;"/>'+
				'			</div>'+
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Compiled condition values <br/><em>(separate each value with "|")</em></div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VALUE )) == null ? '' : __t) + '" /></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Boolean Operator</div><div style="float:right"><select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_OP )) == null ? '' : __t) + '"><option></option><option value="AND">AND</option><option value="OR">OR</option></select></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Value of this field, if the condition is <b>met</b></div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.COMPILA )) == null ? '' : __t) + '" /></div>'+
				'		<div style="clear:both"></div>';
		__p +=  '	</div>'+	
				'	</div>'+
				'	</div>';
	}
	return __p;
};

this["Formbuilder"]["validators"]["validate/value"] = function(obj,current) {
	var is_compila_condition_var = obj.field_options['compila_condition_var'] != '' && obj.field_options['compila_condition_var']!= undefined ? true : false;
	var is_compila_condition_value = obj.field_options['compila_condition_value'] != '' && obj.field_options['compila_condition_value']!= undefined ? true : false;
	var is_compila = obj.field_options['compila'] != '' && obj.field_options['compila']!= undefined ? true : false;
	var is_compila_op = obj.field_options['compila_condition_op'] != '' && obj.field_options['compila_condition_op']!= undefined ? true : false;
	var by_pass_hidden_pk= $.inArray(obj.field_options['var'], ['CODPAT','ESAM','PROGR','VISITNUM','VISITNUM_PROGR','USERID_INS','INVIOCO','CENTER','SITEID','SUBJID']) != -1 ;
	var is_valid=false;
	if(!by_pass_hidden_pk){
		if((is_compila_condition_var && is_compila_condition_value ) || !is_compila_condition_var || !is_compila_condition_value || !is_compila){ //ALMENO UN CAMPO NON VALORIZZATO
			if(is_compila_condition_var && is_compila_condition_value){ //SE VAR E VALUE SONO VALORIZZATI
				var compila_condition_vars=obj.field_options['compila_condition_var'].split('|'); // CONTROLLO CHE ABBIANO LO STESSO NUMERO DI ELEMENTI
				var compila_condition_values=obj.field_options['compila_condition_value'].split('|');
				if(compila_condition_vars.length!=compila_condition_values.length){
					$("div[id='s2id_model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VAR )) == null ? '' : __t) + "']").css("border", "1px solid red");
					$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VALUE )) == null ? '' : __t) + "']").css("border", "1px solid red");
					validation_messages+="<li>The fields \"Compiled condition fields\" and \"Compiled condition values\" must be of the same length</li>";
					/*bootbox.dialog({
							message : "The fields \"Compiled condition fields\" and \"Compiled condition values\" must be of the same length",
							title : 'Validating Form',
							className : "structLoader"});*/
				}
				else{
					is_valid=true;
					$("div[id='s2id_model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VAR )) == null ? '' : __t) + "']").css("border", "");
					$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VALUE )) == null ? '' : __t) + "']").css("border", "");
				}
				if(!is_compila){ //E CONTROLLO CHE IL CAMPO "COMPILA" SIA VALORIZZATO
					is_valid=false;
					$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.COMPILA )) == null ? '' : __t) + "']").css("border", "1px solid red");
					validation_messages+="<li>The field \"Value of this field, if the condition is met\"  must be filled</li>";
					/*bootbox.dialog({
								message : "The field \"Value of this field, if the condition is met\"  must be filled",
								title : 'Validating Form',
								className : "structLoader"});*/
					
				}
				if(!is_compila_op){ //E CONTROLLO CHE IL CAMPO "COMPILA_OP" SIA VALORIZZATO
					is_valid=false;
					$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_OP )) == null ? '' : __t) + "']").css("border", "1px solid red");
					validation_messages+="<li>The field \"Boolean operator\"  must be filled</li>";
					/*bootbox.dialog({
								message : "The field \"Boolean operator\"  must be filled",
								title : 'Validating Form',
								className : "structLoader"});*/
					
				}
			}
			else{//SE VAR E VALUE NON SONO VALORIZZATI ENTRAMBI
				if (is_compila && !is_compila_condition_var && !is_compila_condition_value){ //E COMPILA E' VALORIZZATO LO SVUOTO
					is_valid=false;
					$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.COMPILA )) == null ? '' : __t) + "']").css("border", "1px solid red");
					validation_messages+="<li>The field \"Value of this field, if the condition is met\" must be blank</li>";
					/*bootbox.dialog({
								message : "The field \"Value of this field, if the condition is met\" must be blank",
								title : 'Validating Form',
								className : "structLoader"});*/
				}
				if (is_compila_op && !is_compila_condition_var && !is_compila_condition_value){ //E COMPILA E' VALORIZZATO LO SVUOTO
					is_valid=false;
					$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_OP )) == null ? '' : __t) + "']").css("border", "1px solid red");
					validation_messages+="<li>The field \"Boolean operator\" must be blank</li>";
					/*bootbox.dialog({
								message : "The field \"Boolean operator\" must be blank",
								title : 'Validating Form',
								className : "structLoader"});*/
				}
				if(is_compila_condition_var && !is_compila_condition_value){ //var è valorizzato e value no!
					is_valid=false;
					$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VALUE )) == null ? '' : __t) + "']").css("border", "1px solid red");
					validation_messages+="<li>The field \"Compiled condition values\" must be filled</li>";
					/*bootbox.dialog({
							message : "The field \"Compiled condition values\" must be filled",
							title : 'Validating Form',
							className : "structLoader"});*/
				}
				if(is_compila_condition_value && !is_compila_condition_var){ //value è valorizzato e var no!
					is_valid=false;
					$("div[id='s2id_model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VAR )) == null ? '' : __t) + "']").css("border", "1px solid red");
					validation_messages+="<li>The field \"Compiled condition fields\" must be filled</li>";
					/*bootbox.dialog({
							message : "The field \"Compiled condition fields\" must be filled",
							title : 'Validating Form',
							className : "structLoader"});*/
				}
				if(!is_compila && !is_compila_condition_var && !is_compila_condition_value && !is_compila_op){
					//nessuno compilato allora è true
					is_valid=true;
				}
			}
		}
		else{
			is_valid=true;
		}
	}
	else{
		is_valid=true;
	}
	if(current){
		if(!is_valid){
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VAR )) == null ? '' : __t) + "']").parent().parent().parent().css("border","1px solid red");	
		}
		else{
			$("div[id='s2id_model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VAR )) == null ? '' : __t) + "']").css("border", "");
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VALUE )) == null ? '' : __t) + "']").css("border", "");
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.COMPILA )) == null ? '' : __t) + "']").css("border", "");
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.COMPILA_CONDITION_VAR )) == null ? '' : __t) + "']").parent().parent().parent().css("border","");
		}
	}
	return is_valid ;
};


this["Formbuilder"]["templates"]["edit/values"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape, __j = Array.prototype.join;
	function print() {
		__p += __j.call(arguments, '');
	}

	with (obj) {
		//__p += '<div class=\'fb-edit-section-header\'></div>\n\n';
		__p += 	'	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseValues" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Options'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseValues" class="panel-collapse collapse" style="height: 0px;">';
		if ( typeof includeBlank !== 'undefined') { ;
			__p += '\n<div style="float:left">Include blank</div><div style="float:right"><input type=\'checkbox\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.INCLUDE_BLANK )) == null ? '' : __t) + '\' /></div>\n'+
				   '<div style="clear:both"></div>';
		} ;
		__p += '		<div class=\'option\' data-rv-each-option=\'model.' + (( __t = (Formbuilder.options.mappings.VALUES )) == null ? '' : __t) + '\'>\n '+
			   '			<div class="fb-field-wrapper"><div class="subtemplate-wrapper">'+
			   '				<input type="text" data-rv-input="option:label" class=\'option-label-input\' />&nbsp;label'+
			   '				<input type="text" data-rv-input="option:value" class=\'option-value-input\' />&nbsp;value<br/>\n'+
			   '				<div class=\'actions-wrapper\'>'+
			   '					<a class="js-duplicate js-add-option ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Add Option"><i class=\'fa fa-plus-circle\'></i></a>\n'+
			   '					<a class="js-clear js-remove-option ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Remove Option"><i class=\'fa fa-minus-circle\'></i></a>\n'+
			   '				</div>'+
			   '			</div></div>'+
			   '		</div>\n\n';
			   
		if ( typeof includeOther !== 'undefined') { ;
			__p += '\n  <label>\n    <input type=\'checkbox\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.INCLUDE_OTHER )) == null ? '' : __t) + '\' />\n    Include "other"\n  </label>\n';
		} ;
		__p += '\n\n<div class=\'fb-bottom-add\'>\n  <a class="js-add-option ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '">Add option</a>\n</div>\n';

	}
		__p += '	</div>'+
			   '	</div>'+	
			   '	</div>';
	return __p;
};

this["Formbuilder"]["validators"]["validate/option_values"] = function(obj,current) {
	var is_valid=true;
	var values_array=[]; //controllo se le option sono tutte diverse
	$(obj.value).each(function(key,model){
		
		if(current && $($("#collapseRadioValues").children(".option")[key]).find('input[data-rv-input="option:value"]').val()!==undefined){
			$($("#collapseRadioValues").children(".option")[key]).find('input[data-rv-input="option:value"]').val($($("#collapseRadioValues").children(".option")[key]).find('input[data-rv-input="option:value"]').val().toUpperCase().trim().replace(/ /g, "").replace(/\W/g, "").replace($("#study_prefix").val()+"_",""));
			model.value=$($("#collapseRadioValues").children(".option")[key]).find('input[data-rv-input="option:value"]').val();
		}
		if(model.value!==undefined){
			model.value=model.value.toUpperCase().trim().replace(/ /g, "").replace(/\W/g, "");
			obj.value[key].value=model.value;
			//fb.mainView.editView.model.attributes.value[key].value=model.value;
		}
		
		if(model.value==undefined || model.value==""){
			validation_messages+="<li>All options value must be filled</li>";
			/*bootbox.dialog({
								message : "All options value must be filled",
								title : 'Validating Form',
								className : "structLoader"});*/
			is_valid=is_valid && false;
			if(current){
				$($("#collapseRadioValues").children(".option")[key]).css("border","1px solid red");
				$("#collapseRadioValues").parent().css("border","1px solid red");
			}
		}
		else{
			if(current){
				$($("#collapseRadioValues").children(".option")[key]).css("border","");
			}
			values_array[model.value]=values_array[model.value] == undefined ? 1 : values_array[model.value]+1; //controllo univocità dei valori nelle options
			if(values_array[model.value]>1){
				is_valid=is_valid && false;
				if(current){
					$($("#collapseRadioValues").children(".option")[key]).css("border","1px solid red");
					$("#collapseRadioValues").parent().css("border","1px solid red");
					validation_messages+='<li>Please use distinct values for the options</li>';
				}
			}
			else{
				if(current){
					$($("#collapseRadioValues").children(".option")[key]).css("border","");
				}
			}
			if(obj.field_type==="checkbox"){
				is_valid=is_valid && Formbuilder.validators['validate/table_column_name_valid'](obj,current,model.value,false);
				if(current){
					if(is_valid){
						$($("#collapseRadioValues").children(".option")[key]).css("border","");
						$("#collapseRadioValues").parent().css("border","");
					}
					else{
						$($("#collapseRadioValues").children(".option")[key]).css("border","1px solid red");
						$("#collapseRadioValues").parent().css("border","1px solid red");
					}
				}
				/*
				////controllo univocità values delle opption con altri nomi di colonna	
				var fields=fb.mainView.bootstrapData;//JSON.parse($("#form_fields").val());
			
				//mi prendo tutti i .var attuali
				var columns = $.map( fields, function( field ) {
					if( (field.field_type!=="form") && (obj.cid!=field.cid)){
						return field.field_options.var;
					}
					return undefined;
				});
				var options=new Array(); //prendo anche tutte le option dei checkbox
					$(fields).each( function( key_field,field ) {
						if(field.field_type=="checkbox"){
							options=$.map( field.value, function( check_values ) {
								if (obj.cid!=field.cid){
					                	return check_values.value;
					            }
				           	});
				        }
						return undefined;
					});
				if(options.length>0){	
					$.merge(columns,options);
				}
				if($.inArray(model.value,columns)>0){ //non faccio controllo sull'esistenza del nome della colonna per campi label (text)
					is_valid=is_valid && false;
					if(current){
						validation_messages+="<li>The column name is already used!</li>";
						$($("#collapseRadioValues").children(".option")[key]).css("border","1px solid red");
						$("#collapseRadioValues").parent().css("border","1px solid red");
					}
				}
				if (model.value.length > 20){
					is_valid=is_valid && false;
					if(current){
						validation_messages+="<li>The column name can't exceed 20 characters!</li>";
						$($("#collapseRadioValues").children(".option")[key]).css("border","1px solid red");
						$("#collapseRadioValues").parent().css("border","1px solid red");
					}
				}
				
				if ( /^\d/.test(model.value)){
					is_valid=is_valid && false;
					if(current){
						validation_messages+="<li>The column name can't start with a numeric character!</li>";
						$($("#collapseRadioValues").children(".option")[key]).css("border","1px solid red");
						$("#collapseRadioValues").parent().css("border","1px solid red");
					}
				}
				if ( $.inArray(model.value,Formbuilder.utils.oracle_reserved_words)>=0){
					is_valid=is_valid && false;
					if(current){
						validation_messages+="<li>This column name can't be used because it is a reserved word!</li>";
						$($("#collapseRadioValues").children(".option")[key]).css("border","1px solid red");
						$("#collapseRadioValues").parent().css("border","1px solid red");
					}
				}*/
			}
			
		}
		
	});
	if(is_valid&&current){
		$("#collapseRadioValues").parent().css("border","");
	}
	else{
		
	}
	return is_valid ;
};

this["Formbuilder"]["templates"]["edit/radio_values"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape, __j = Array.prototype.join;
	function print() {
		__p += __j.call(arguments, '');
	}

	with (obj) {
		//__p += '<div class=\'fb-edit-section-header\'></div>\n\n';
		__p += 	'	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseRadioValues" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Options'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseRadioValues" class="panel-collapse collapse" style="height: 0px;">';
		if ( typeof includeBlank !== 'undefined') { 
			__p += '\n<div style="float:left">Include blank</div><div style="float:right"><input type=\'checkbox\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.INCLUDE_BLANK )) == null ? '' : __t) + '\' /></div>\n'+
				   '<div style="clear:both"></div>';
		} ;
		__p +=	'		<div style="float:left">Options per row</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.SUBTBCOL )) == null ? '' : __t) + '" /></div>' +
				'		<div style="clear:both"></div>';
		__p += 	'		<div class=\'option\' data-rv-each-option=\'model.' + (( __t = (Formbuilder.options.mappings.VALUES )) == null ? '' : __t) + '\'>\n '+
			    '			<div class="fb-field-wrapper"><div class="subtemplate-wrapper">'+
			    '				<div style="float:left">Checked</div><div style="float:right"><input type="checkbox" class=\'js-default-updated\' data-rv-checked="option:checked" /></div>'+
			    '				<div style="clear:both"></div>'+
			    '				<div style="float:left">Disabled</div><div style="float:right"><input type="checkbox" class=\'js-default-updated _disabled\' data-rv-checked="option:disabled_val" /></div> '+
			    '				<div style="clear:both"></div>'+
			    '				<div style="float:left">label</div><div style="float:right"><input type="text" data-rv-input="option:label" class=\'option-label-input\' />&nbsp;</div>'+
			    '				<div style="clear:both"></div>'+
			    '				<div style="float:left">value</div><div style="float:right"><input type="text" data-rv-input="option:value" class=\'option-value-input\' />&nbsp;</div>\n'+
			    '				<div style="clear:both"><br/></div>'+
			    '				<div class=\'actions-wrapper\'>'+
			    '					<a class="js-duplicate js-add-option ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Add Option"><i class=\'fa fa-plus-circle\'></i></a>\n'+
			    '					<a class="js-clear js-remove-option ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Remove Option"><i class=\'fa fa-minus-circle\'></i></a>\n'+
			    '				</div>'+
			    '			</div></div>'+
			    '		</div>\n\n';
			   
		if ( typeof includeOther !== 'undefined') { ;
			__p += '\n  <label>\n    <input type=\'checkbox\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.INCLUDE_OTHER )) == null ? '' : __t) + '\' />\n    Include "other"\n  </label>\n';
		} ;
		__p += '\n\n<div class=\'fb-bottom-add\'>\n  <a class="js-add-option ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '">Add option</a>\n</div>\n';

	}
		__p += '	</div>'+
			   '	</div>'+	
			   '	</div>';
	return __p;
};


this["Formbuilder"]["templates"]["edit/main_sub"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape, __j = Array.prototype.join;
	function print() {
		__p += __j.call(arguments, '');
	}

	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapsePK" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;If it is part of a main form'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapsePK" class="panel-collapse collapse" style="height: 0px;">'+
				'	<div style="float:left">It is used in a sub form</div><div style="float:right"><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.MAIN )) == null ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.MAIN )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.MAIN )) == null ? '' : __t) + '\' /></div>\n'+
				'	<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'	</div>';
		//__p += '\n  <div class=\'fb-edit-section-header\'>&nbsp;</div><label><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.UPPERCASE )) == null ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.UPPERCASE )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.UPPERCASE )) == null ? '' : __t) + '\' />Uppercase\n</label>\n';
	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/var_type"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseVarType" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Variable Type'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseVarType" class="panel-collapse collapse" style="height: 0px;">'+
				'		<select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.VAR_TYPE )) == null ? '' : __t) + '">\n  <option value="text">Text</option>\n  <option value="number">Number</option>\n\n</select>\n'+
				'	</div>';
		//__p += '<div class=\'fb-edit-section-header\'>Var Type</div>\n<select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.VAR_TYPE )) == null ? '' : __t) + '">\n  <option value="text">Text</option>\n  <option value="number">Number</option>\n\n</select>\n';

	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/var_size"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseVarSize" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Variable Size'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseVarSize" class="panel-collapse collapse" style="height: 0px;">'+
				'		<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.VAR_SIZE )) == null ? '' : __t) + '" />'+
				'	</div>';
		//__p += '<div class=\'fb-edit-section-header\'>Var Type</div>\n<select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.VAR_TYPE )) == null ? '' : __t) + '">\n  <option value="text">Text</option>\n  <option value="number">Number</option>\n\n</select>\n';

	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/fm_code"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += '<div class=\'fb-edit-section-header\'>FM Code</div>\n<select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.FM_CODE )) == null ? '' : __t) + '">\n  <option value="01">NK</option>\n  <option value="02">NA</option>\n  <option value="03">NK,NA</option>\n\n</select>\n';

	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/save_send"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=	'	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseSaveSend" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Is the field mandatory'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseSaveSend" class="panel-collapse collapse" style="height: 0px;">'+
				'		<div style="float:left">On save event</div><div style="float:right"><select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.SAVE )) == null ? '' : __t) + '">\n  <option value="facoltativo">Not mandatory</option>\n  <option value="obbligatorio">Mandatory</option>\n\n</select></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">On send event</div><div style="float:right"><select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.SEND )) == null ? '' : __t) + '">\n  <option value="facoltativo">Not mandatory</option>\n  <option value="obbligatorio">Mandatory</option>\n\n</select></div>' +
				'		<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'	</div>';	

	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/checkbox_save_send"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=	'	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseSaveSend" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Is the field mandatory'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseSaveSend" class="panel-collapse collapse" style="height: 0px;">'+
				'		<div style="float:left">On save event</div><div style="float:right"><label><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.GROUP_SAVE )) == 'obbligatorio' ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.GROUP_SAVE )) == 'obbligatorio' ? '' : __t ) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.GROUP_SAVE )) == 'obbligatorio' ? '' : __t) + '\' /></label></div>'+
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">On send event</div><div style="float:right"><label><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.GROUP_SEND )) == 'obbligatorio' ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.GROUP_SEND )) == 'obbligatorio' ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.GROUP_SEND )) == 'obbligatorio' ? '' : __t) + '\' /></label></div>'+
				'		<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'	</div>';	

	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/db_info"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseColumnName" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Database column info'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseColumnName" class="panel-collapse collapse" style="height: 0px;">'+
				'		<div style="float:left">Name</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + '" /></div>'+
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Type</div><div style="float:right"><select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.VAR_TYPE )) == null ? '' : __t) + '">\n  <option value="text">Text</option>\n  <option value="number">Number</option>\n\n</select></div>'+
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Size</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.VAR_SIZE )) == null ? '' : __t) + '" /></div>'+
				'		<div style="clear:both"></div>'+
				/*'		<div style="float:left">Primary Key</div><div style="float:right"><label><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.PK )) == null ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.PK )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.PK )) == null ? '' : __t) + '\' /></label></div>'+
				'		<div style="clear:both"></div>'+*/
				'		<div style="float:left">Don\'t create relative column in database</div><div style="float:right"><label><input type=\'checkbox\' value=\''+(( __t = (Formbuilder.options.mappings.TB )) == null ? '' : __t) +'\' name=\''+(( __t = (Formbuilder.options.mappings.TB )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.TB )) == null ? '' : __t) + '\' /></label></div>'+				
				'		<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'	</div>';
		//__p += '<div class=\'fb-edit-section-header\'>Column Name:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + '" />\n';
	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/db_info_label"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseColumnName" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Database column info'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseColumnName" class="panel-collapse collapse" style="height: 0px;">'+
				'		<div style="float:left">Name</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + '" /></div>'+
				'		<div style="clear:both"></div>'+
				/*'		<div style="float:left">Type</div><div style="float:right"><select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.VAR_TYPE )) == null ? '' : __t) + '">\n  <option value="text">Text</option>\n  <option value="number">Number</option>\n\n</select></div>'+
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Size</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.VAR_SIZE )) == null ? '' : __t) + '" /></div>'+
				'		<div style="clear:both"></div>'+*/
				/*'		<div style="float:left">Primary Key</div><div style="float:right"><label><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.PK )) == null ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.PK )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.PK )) == null ? '' : __t) + '\' /></label></div>'+
				'		<div style="clear:both"></div>'+*/
				'		<div style="float:left">Don\'t create relative column in database</div><div style="float:right"><label><input type=\'checkbox\' value=\''+(( __t = (Formbuilder.options.mappings.TB )) == null ? '' : __t) +'\' name=\''+(( __t = (Formbuilder.options.mappings.TB )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.TB )) == null ? '' : __t) + '\' /></label></div>'+				
				'		<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'	</div>';
		//__p += '<div class=\'fb-edit-section-header\'>Column Name:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + '" />\n';
	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/db_info_date"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseColumnName" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Database column info'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseColumnName" class="panel-collapse collapse" style="height: 0px;">'+
				'		<div style="float:left">Name</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + '" /></div>'+
				'		<div style="clear:both"></div>'+
				/*'		<div style="float:left">Type</div><div style="float:right"><select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.VAR_TYPE )) == null ? '' : __t) + '">\n  <option value="text">Text</option>\n  <option value="number">Number</option>\n\n</select></div>'+
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Size</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.VAR_SIZE )) == null ? '' : __t) + '" /></div>'+
				'		<div style="clear:both"></div>'+*/
				/*'		<div style="float:left">Primary Key</div><div style="float:right"><label><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.PK )) == null ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.PK )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.PK )) == null ? '' : __t) + '\' /></label></div>'+
				'		<div style="clear:both"></div>'+*/
				'		<div style="float:left">Don\'t create relative column in database</div><div style="float:right"><label><input type=\'checkbox\' value=\''+(( __t = (Formbuilder.options.mappings.TB )) == null ? '' : __t) +'\' name=\''+(( __t = (Formbuilder.options.mappings.TB )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.TB )) == null ? '' : __t) + '\' /></label></div>'+				
				'		<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'	</div>';
		//__p += '<div class=\'fb-edit-section-header\'>Column Name:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + '" />\n';
	}
	return __p;
};

this["Formbuilder"]["validators"]["validate/db_info"] = function(obj,current) {
	
	/**setto tb=no se il check tb è cliccato*/
	if($("input[data-rv-checked='model." + (( __t = (Formbuilder.options.mappings.TB )) == null ? '' : __t) + "']").prop('checked')){
		fb.mainView.editView.model.attributes.field_options.tb="no";
	}
	if(current && $("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").val()!==undefined){
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").val($("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").val().toUpperCase().trim().replace(/ /g, "").replace(/\W/g, "").replace($("#study_prefix").val()+"_",""));
		fb.mainView.editView.model.attributes.field_options.var=$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").val();
		obj.field_options['var']=$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").val();
	}
	// if(obj.field_type==="text" && (obj.field_options['var']===undefined || obj.field_options['var']==="")){
		// //fb.mainView.editView.model.attributes.field_options.var=fb.mainView.editView.model.attributes.field_options.var.toUpperCase().trim().replace(/ /g, "").replace($("#study_prefix").val()+"_","");
		// obj.field_options['var']="_LABELFIELD";
	// }
	if(obj.field_options['var']!==undefined){
		obj.field_options['var']=obj.field_options['var'].toUpperCase().trim().replace(/ /g, "").replace(/\W/g, "");
		
	}
	
	var my_field= obj.field_options['var'];
	var is_valid_var = Formbuilder.validators['validate/table_column_name_valid'](obj,current,my_field,false);//my_field!==undefined && my_field !="" && my_field.length <=20 && !/^\d/.test(my_field)  && $.inArray(my_field,Formbuilder.utils.oracle_reserved_words)<0 ? true : false;
	if(is_valid_var){
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").css("border","");
	}
	else{
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").css("border","1px solid red");
		
		/*var fields=fb.mainView.bootstrapData;//JSON.parse($("#form_fields").val());
		
		//mi prendo tutti i .var attuali
		var columns = $.map( fields, function( field ) {
			if( (field.field_type!=="form") && (obj.cid!=field.cid)){
				return field.field_options.var;
			}
			return undefined;
		});
		var options=new Array(); //prendo anche tutte le option dei checkbox
			$(fields).each( function( key_field,field ) {
				if(field.field_type=="checkbox"){
					options=$.map( field.value, function( check_values ) {
						if (obj.cid!=field.cid){
			                	return check_values.value;
			            }
		           	});
		        }
				return undefined;
			});
			
		if(options.length>0){	
			$.merge(columns,options);
		}
		if(obj.field_type!=='text' && $.inArray(my_field,columns)>0){ //non faccio controllo sull'esistenza del nome della colonna per campi label (text)
			is_valid_var=false;
			
			if(current){
				validation_messages+="<li>The column name is already used!</li>";
				$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").css("border","1px solid red");
			}
		}
		if (my_field.length > 20){
			is_valid_var=false;
			
			if(current){
				validation_messages+="<li>The column name can't exceed 20 characters!</li>";
				$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").css("border","1px solid red");
			}
		}
		if ( /^\d/.test(my_field)){
			is_valid_var=false;
			
			if(current){
				validation_messages+="<li>The column name can't start with a numeric character!</li>";
				$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").css("border","1px solid red");
			}
		}
		if ( $.inArray(my_field,Formbuilder.utils.oracle_reserved_words)>=0){
			is_valid_var=false;
			
			if(current){
				validation_messages+="<li>This column name can't be used because it is a reserved word!</li>";
				$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").css("border","1px solid red");
			}
		}
		if(my_field===undefined || my_field ==""){
			is_valid_var=false;
			
			if(current){
				validation_messages+="<li>The column name must be specified!</li>";
				$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").css("border","1px solid red");
			}
		}*/
	}
	var is_valid_var_size =true; //se è una data o una label (text) non devo validarli perchè type e size non sono presenti
	var is_valid_var_type =true;
	
	
	if(obj.field_type!=='date_cal' && obj.field_type!=='text'){
		if(current && ($("select[data-rv-value='model."+ (( __t = (Formbuilder.options.mappings.VAR_TYPE )) == null ? '' : __t) + "']").val()===null|| $("select[data-rv-value='model."+ (( __t = (Formbuilder.options.mappings.VAR_TYPE )) == null ? '' : __t) + "']").val()=="")){
			$("select[data-rv-value='model."+ (( __t = (Formbuilder.options.mappings.VAR_TYPE )) == null ? '' : __t) + "']").val("text").change();
			fb.mainView.editView.model.attributes.field_options.var_type="text";
			obj.field_options['var_type']="text";
			is_valid_var_type=true;
		}
		else{
			is_valid_var_type = obj.field_options['tb']=='no' || (obj.field_options['var_type'] != '' && obj.field_options['var_type'] != undefined) ? true : false;
		}
		if(!is_valid_var_type){
			if(current){
				$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.VAR_TYPE )) == null ? '' : __t) + "']").css("border", "1px solid red");
				/*bootbox.dialog({
						message : "Column type is required!",
						title : 'Validating Form',
						className : "structLoader"});*/
				validation_messages+="<li>Column type is required!</li>";
			}
		}
		else{
			if(current){
				$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.VAR_TYPE )) == null ? '' : __t) + "']").css("border","");
			}
		}
		is_valid_var_size = obj.field_options['tb']=='no' || (obj.field_options['var_size'] != '' && obj.field_options['var_size'] != undefined && !isNaN(obj.field_options['var_size'])) || obj.field_options['var_type']=='number' ? true : false;
		if(!is_valid_var_size){
			if(current){
				if(isNaN(obj.field_options['var_size'])){
					validation_messages+="<li>Column size must be a number!</li>";
				}
				if(obj.field_options['var_size'] === '' || obj.field_options['var_size'] === undefined){
					validation_messages+="<li>Column size is required!</li>";	
				}
				$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR_SIZE )) == null ? '' : __t) + "']").css("border", "1px solid red");
			}
		}
		else{
			if(current){
				$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR_SIZE )) == null ? '' : __t) + "']").css("border","");
			}
			
		}
	}
	var is_valid=is_valid_var && is_valid_var_size && is_valid_var_type;
	if(!is_valid){
		if(current){
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").parent().parent().parent().css('border','1px solid red');
		}
	}
	else{
		if(current){
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").parent().parent().parent().css('border','');
		}
	}
	return is_valid ;
};

this["Formbuilder"]["templates"]["edit/bytb"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseByTB" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Get Value from DB'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseByTB" class="panel-collapse collapse" style="height: 0px;">' +
				'		<div style="float:left">TABLE field</div><div style="float:right"><select  data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.BYTB )) == null ? '' : __t) + '" /><option value=""></option></div>'+
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Without Study Prefix </div><div style="float:right"><label><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.BYTBNOPREFIX )) == null ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.BYTBNOPREFIX )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.BYTBNOPREFIX )) == null ? '' : __t) + '\' /></label></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">CODE field</div><div style="float:right"><select  data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.BYTBCODE )) == null ? '' : __t) + '" ><option value=""></option></select></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">DECODE field</div><div style="float:right"><select  data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.BYTBDECODE )) == null ? '' : __t) + '" ><option value=""></option></select></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">WHERE clause</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.BYTBWHERE )) == null ? '' : __t) + '" /></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">ORDER BY</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.BYTBORDERBY )) == null ? '' : __t) + '" /></div>' +
				'		<div style="clear:both"></div>'+
				/*'		<div style="float:left">BYVAR</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.BYVAR )) == null ? '' : __t) + '" /></div>' +
				'		<div style="clear:both"></div>'+*/
				'	</div>'+
				'	</div>'+
				'	</div>';
	}
	return __p;
};

this["Formbuilder"]["validators"]["validate/bytb"] = function(obj,current) {
	var is_bytb = obj.field_options['bytb'] != '' && obj.field_options['bytb']!= undefined ? true : false;
	var is_bytbnoprefix = obj.field_options['bytbnoprefix'] != '' && obj.field_options['bytbnoprefix']!= undefined ? true : false;
	var is_bytbcode = obj.field_options['bytbcode'] != '' && obj.field_options['bytbcode']!= undefined ? true : false;
	var is_bytbdecode = obj.field_options['bytbdecode'] && obj.field_options['bytbdecode']!= undefined != '' ? true : false;
	var is_bytbwhere = obj.field_options['bytbwhere'] && obj.field_options['bytbwhere']!= undefined != '' ? true : false;
	var is_valid=is_bytb && is_bytbcode && is_bytbdecode && is_bytbwhere || (!is_bytb && !is_bytbcode && !is_bytbdecode && !is_bytbwhere);
	if(!is_valid){
		if(current){
			if(is_bytb){
				if(!is_bytbcode){
					$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.BYTBCODE )) == null ? '' : __t) + "']").css("border", "1px solid red");
					validation_messages+="<li>CODE field is required if TABLE field is compiled</li>";
					/*bootbox.dialog({
							message : "CODE field is required if TABLE field is compiled",
							title : 'Validating Form',
							className : "structLoader"});*/
				}
				else{
					$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.BYTBCODE )) == null ? '' : __t) + "']").css("border","");
				}
				if(!is_bytbdecode){
					$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.BYTBDECODE )) == null ? '' : __t) + "']").css("border", "1px solid red");
					validation_messages+="<li>DECODE field is required if TABLE field is compiled</li>";
					/*bootbox.dialog({
							message : "DECODE field is required if TABLE field is compiled",
							title : 'Validating Form',
							className : "structLoader"});*/
				}
				else{
					$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.BYTBDECODE )) == null ? '' : __t) + "']").css("border","");
				}
				if(!is_bytbwhere){
					$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.BYTBWHERE )) == null ? '' : __t) + "']").css("border", "1px solid red");
					validation_messages+="<li>WHERE clause is required if TABLE field is compiled</li>";
					/*bootbox.dialog({
							message : "WHERE clause is required if TABLE field is compiled",
							title : 'Validating Form',
							className : "structLoader"});*/
				}
				else{
					$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.BYTBWHERE )) == null ? '' : __t) + "']").css("border","");
					
				}
			}
			else{
				if(!is_bytb && is_bytbcode && is_bytbdecode && is_bytbwhere){
					$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.BYTB)) == null ? '' : __t) + "']").css("border", "1px solid red");
					validation_messages+="<li>TABLE field is required if all other attributes are compiled</li>";
					/*bootbox.dialog({
							message : "TABLE field is required if all other attributes are compiled",
							title : 'Validating Form',
							className : "structLoader"});*/
				}
				else{
					$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.BYTB)) == null ? '' : __t) + "']").css("border","");
				}
				
			}
		}
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.BYTBWHERE )) == null ? '' : __t) + "']").parent().parent().parent().css('border','1px solid red');
	}
	else{
		if(current){
			$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.BYTB )) == null ? '' : __t) + "']").css("border", "");
			$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.BYTBCODE )) == null ? '' : __t) + "']").css("border", "");
			$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.BYTBDECODE )) == null ? '' : __t) + "']").css("border", "");
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.BYTBWHERE )) == null ? '' : __t) + "']").css("border", "");
			$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.BYTB )) == null ? '' : __t) + "']").parent().parent().parent().css('border','');
		}
		
	}
	
	return is_valid ;
};

this["Formbuilder"]["templates"]["edit/condition"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseCondition" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Visibility under condition'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseCondition" class="panel-collapse collapse" style="height: 0px;">' +
				' 		<div class=\'fb-edit-section-header\'>Simple Condition</div>'+
				'		<div style="float:left">Condition field</div><div style="float:right"><select  data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.CONDITION )) == null ? '' : __t) + '" /><option value=""></option></div>'+
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Condition value</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.CONDITION_VALUE )) == null ? '' : __t) + '" /></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left"><em>The condition is true if the value of the selected Condition field is <b>equal</b> to the condition value</em></div>'+
				'		<div style="clear:both"></div>'+
				'		<div class=\'fb-edit-section-header\'>Behaviours</div>'+
				'		<div style="float:left">Alert message to show if the condition <b>is not met</b></div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.LABEL_JS )) == null ? '' : __t) + '" style="width: 250px" /></div>'+
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Hide the field if the condition <b>is not met</b></div><div style="float:right"><label><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.HIDE )) == null ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.HIDE )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.HIDE )) == null ? '' : __t) + '\' /></label></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Hide the field,<br/><em>when the form is closed</em></div><div style="float:right"><label><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.HIDEVIS )) == null ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.HIDEVIS )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.HIDEVIS )) == null ? '' : __t) + '\' /></label></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Show the field,<br/><em>when the form is closed</em></div><div style="float:right"><label><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.SHOW_VIS )) == null ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.SHOW_VIS )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.SHOW_VIS )) == null ? '' : __t) + '\' /></label></div>' +
				'		<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'	</div>';
	}
	return __p;
};

this["Formbuilder"]["validators"]["validate/condition"] = function(obj,current) {
	var is_condition = obj.field_options['condition'] != '' && obj.field_options['condition']!= undefined ? true : false;
	var is_condition_value = obj.field_options['condition_value'] != '' && obj.field_options['condition_value']!= undefined ? true : false;
	var is_hidevis = obj.field_options['hidevis'] != '' && obj.field_options['hidevis']!= undefined ? true : false;
	var is_hide = obj.field_options['hide'] != '' && obj.field_options['hide']!= undefined ? true : false;
	var is_valid=( ( !( is_condition && !is_condition_value ) ) && ( !( is_condition_value && !is_condition ) ) ) && !(is_hidevis &&  is_hide) ; // doppia implicazione is_condition<==>is_condition_value
	if(!is_valid){
		if(current){
			if(is_condition && !is_condition_value ){
				$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.CONDITION_VALUE )) == null ? '' : __t) + "']").css("border", "1px solid red");
				bootbox.dialog({
						message : "Condition value is required if Condition field is compiled",
						title : 'Validating Form',
						className : "structLoader"});
				
			}
			else if(!is_condition && is_condition_value ){
				$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.CONDITION )) == null ? '' : __t) + "']").css("border", "1px solid red");
				bootbox.dialog({
						message : "Condition field is required if Condition value is compiled",
						title : 'Validating Form',
						className : "structLoader"});
				
			}
			if(is_hidevis &&  is_hide){
				$("input[data-rv-checked='model." + (( __t = (Formbuilder.options.mappings.HIDEVIS )) == null ? '' : __t) + "']").parent().css("border", "1px solid red");
				$("input[data-rv-checked='model." + (( __t = (Formbuilder.options.mappings.HIDE )) == null ? '' : __t) + "']").parent().css("border", "1px solid red");
				bootbox.dialog({
						message : "The checboxes are mutually exlusives",
						title : 'Validating Form',
						className : "structLoader"});
			}
		}
		$("input[data-rv-checked='model." + (( __t = (Formbuilder.options.mappings.HIDE )) == null ? '' : __t) + "']").parent().parent().parent().parent().css('border','1px solid red');
	}
	else{
		if(current){
			$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.CONDITION )) == null ? '' : __t) + "']").css("border", "");
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.CONDITION_VALUE )) == null ? '' : __t) + "']").css("border", "");
			$("input[data-rv-checked='model." + (( __t = (Formbuilder.options.mappings.HIDEVIS )) == null ? '' : __t) + "']").parent().css("border", "");
			$("input[data-rv-checked='model." + (( __t = (Formbuilder.options.mappings.HIDE )) == null ? '' : __t) + "']").parent().css("border", "");
			$("select[data-rv-value='model." + (( __t = (Formbuilder.options.mappings.CONDITION )) == null ? '' : __t) + "']").parent().parent().parent().css('border','');
		}
		
	}
	
	return is_valid ;
};

this["Formbuilder"]["templates"]["edit/formatting"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseVisibility" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Field formatting'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseVisibility" class="panel-collapse collapse" style="height: 0px;">' +
				'		<div style="float:left">Hide Label</div><div style="float:right"><label><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.HIDE_LABEL )) == null ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.HIDE_LABEL )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.HIDE_LABEL )) == null ? '' : __t) + '\' /></label></div>'+
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Size</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.SIZE )) == null ? '' : __t) + '" /></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Cols</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.FIELD_COLS )) == null ? '' : __t) + '" /></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Colspan</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.COLSPAN )) == null ? '' : __t) + '" /></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Text align</div><div style="float:right"><select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.TXT_ALIGN )) == null ? '' : __t) + '">\n  <option value="left">left</option>\n  <option value="center">center</option>\n  <option value="right" selected="selected">right</option>\n</select></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Field align</div><div style="float:right"><select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.FIELD_ALIGN )) == null ? '' : __t) + '">\n  <option value="left" selected="selected">left</option>\n  <option value="center">center</option>\n  <option value="right">right</option>\n</select></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Right Label</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.DEF )) == null ? '' : __t) + '" /></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Automatically change the content<br/>to upper case</div><div style="float:right"><label><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.UPPER )) == null ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.UPPER )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.UPPER )) == null ? '' : __t) + '\' /></label></div>'+
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Disabled</div><div style="float:right"><label><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.DISABLED )) == null ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.DISABLED )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.DISABLED )) == null ? '' : __t) + '\' /></label></div>'+
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Mask as password</div><div style="float:right"><label><input type=\'checkbox\' value=\' '+(( __t = (Formbuilder.options.mappings.CRYPTO )) == null ? '' : __t) +'\' name=\' '+(( __t = (Formbuilder.options.mappings.CRYPTO )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.CRYPTO )) == null ? '' : __t) + '\' /></label></div>'+
				'		<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'	</div>';
	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/javascript"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseJavascript" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Javascript code'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseJavascript" class="panel-collapse collapse" style="height: 0px;">' +
				'		<div style="float:left">Action type</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.ACTION_TYPE )) == null ? '' : __t) + '" /></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">On Action</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.ON_ACTION )) == null ? '' : __t) + '" /></div>' +
				'		<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'	</div>';
	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/tb"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseTB" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Update DB'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseTB" class="panel-collapse collapse" style="height: 0px;">'+
				'		<label><input type=\'checkbox\' value=\''+(( __t = (Formbuilder.options.mappings.TB )) == 'no' ? '1' : '') +'\' name=\''+(( __t = (Formbuilder.options.mappings.TB )) == null ? '' : __t) +'\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.TB )) == null ? '' : __t) + '\' />&nbsp;Don\'t create relative column in database</label>\n'+
				'		<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'	</div>';
		//__p += '<div class=\'fb-edit-section-header\'>Column Name:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + '" />\n';
	}
	return __p;
};
//EDIT ATTRIBUTI ENABLE
this["Formbuilder"]["templates"]["edit/enable_list"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseEnableList" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Visits/exams enabled after the freezing of this form'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseEnableList" class="panel-collapse collapse" style="height: 0px;">';
		__p += 	'		<div class=\'option\' data-rv-each-option=\'model.' + (( __t = (Formbuilder.options.mappings.ENABLE )) == null ? '' : __t) + '\'>\n '+
				'			<div style="float:left"><label><input type=\'checkbox\' onclick=\'fb.mainView.formSaved=false;fb.mainView.handleFormUpdate();\' name=\'option:visit_short_txt\' data-rv-checked=\'option:enable\' /></label>&nbsp;</div>\n'+
			   	'			<div style="float:left"><span data-rv-text="option:visit_short_txt"></div><div style="float:left"><span>&nbsp;-&nbsp;</span></div><div style="float:left"><span data-rv-text="option:exam_text"></span></div>\n'+
			   	'			<div style="clear:both"></div>'+
			   	'		</div>\n\n'; 
		__p +=	'	</div>'+
				'	</div>'+
				'	</div>';
		//__p += '<div class=\'fb-edit-section-header\'>Form title:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.TITOLO )) == null ? '' : __t) + '" />\n';
	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/lifecycle_activity"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseLifecycleActivity" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Lifecycle Activity'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseLifecycleActivity" class="panel-collapse collapse" style="height: 0px;">' +
				'		<div style="float:left">This form will trigger the following<br/>Lifecycle Activity</div><div style="float:right">'+
				'			<select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.LIFECYCLE_ACTIVITY )) == null ? '' : __t) + '">'+
				'				<option value="2" >Subject Death</option>'+
				'				<option value="6" >Discontinued</option>'+
				'				<option value="8" >Completed Treatment</option>'+
				'				<option value="9" >Randomized</option>'+
				'				<option value="10">Screen Failed</option>'+
				'				<option value="11">Screened</option>'+
				'				<option value="24">First Informed Consent Signed</option>'+
				'				<option value="25">Subject Visit Date</option>'+
				'				<option value="26">Subject First Treatment Visit Date</option>'+
				'				<option value="27">Subject Last Treatment Visit Date</option>'+
				'			</select>'+
				'       </div>' +
				'		<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'	</div>';
		//__p += '<div class=\'fb-edit-section-header\'> Redirecting links to:';
		//__p += '<div>- after saving the form:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.LINK_TO )) == null ? '' : __t) + '" />\n';
		//__p += '<div>- after sending the form:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.LINK_TO_SEND )) == null ? '' : __t) + '" />\n';
		//__p += '</div>\n';
	}
	return __p;
};

//VALIDAZIONE ATTRIBUTI FORM
this["Formbuilder"]["validators"]["validate/form"] = function(obj,current) {
	var valid=false;
	//TODO GESTIRE UN UNICO ALERT CON I VARI MESSAGGI DI ERRORE (vedi bootbox.dialog in validate/form_name)
	valid_form_name = Formbuilder.validators['validate/form_name'](obj,current);  
	valid_form_title = Formbuilder.validators['validate/form_title'](obj,current);
	valid_form_table = Formbuilder.validators['validate/form_table'](obj,current);
	valid_form_links = Formbuilder.validators['validate/form_links'](obj,current);
	valid_form_main_sub = Formbuilder.validators['validate/form_main_sub'](obj,current);
	valid_form_buttons = Formbuilder.validators['validate/form_buttons'](obj,current);
	valid=valid_form_name && valid_form_title && valid_form_table && valid_form_links && valid_form_main_sub && valid_form_buttons;
	if(!valid){
		$('#field_view_'+obj.cid).addClass('error');
		if(validation_messages!==""){
			bootbox.dialog({
						message : "<ul>"+validation_messages+"</ul>",
						title : 'Validating Form',
						className : "structLoader"});
			validation_messages="";
		}
	}
	else{
		if(validation_confirmation_messages!==""){
					bootbox.alert({
							message : "<ul>"+validation_confirmation_messages+"</ul>",
							title : 'Validating Form',
							className : "structLoader",
							});
							validation_confirmation_messages="";
				}
		$('#field_view_'+obj.cid).removeClass('error');
		
	}
	return valid;
};

this["Formbuilder"]["validators"]["validate/form_name"] = function(obj,current) {
	//alert("CIAO");
	var is_valid = obj.form_options['fname'] != '' ? true : false;
	if(!is_valid){
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.FNAME )) == null ? '' : __t) + "']").css("border", "1px solid red");
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.FNAME )) == null ? '' : __t) + "']").parent().parent().css('border','1px solid red');
		validation_messages+="<li>Form name is required!</li>";
		/*bootbox.dialog({
					message : "Form name is required!",
					title : 'Validating Form',
					className : "structLoader"});*/
	}
	else{
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.FNAME )) == null ? '' : __t) + "']").css("border","");
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.FNAME )) == null ? '' : __t) + "']").parent().parent().css('border','');
	}
	return is_valid;
};
this["Formbuilder"]["validators"]["validate/form_title"] = function(obj,current) {
	//alert("CIAO");
	var is_valid = obj.form_options['titolo'] != '' ? true : false;
	if(!is_valid){
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TITOLO )) == null ? '' : __t) + "']").css("border", "1px solid red");
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TITOLO )) == null ? '' : __t) + "']").parent().parent().css("border", "1px solid red");
	}
	else{
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TITOLO )) == null ? '' : __t) + "']").css("border","");
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TITOLO )) == null ? '' : __t) + "']").parent().parent().css("border","");
	}
	return is_valid ;
};
this["Formbuilder"]["validators"]["validate/form_table"] = function(obj,current) {
	if($("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TABLE )) == null ? '' : __t) + "']").val()!==undefined){
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TABLE )) == null ? '' : __t) + "']").val($("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TABLE )) == null ? '' : __t) + "']").val().toUpperCase().trim().replace(/ /g, "").replace(/\W/g, "").replace($("#study_prefix").val()+"_",""));
		obj.form_options['table']=$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TABLE )) == null ? '' : __t) + "']").val();
	}
	var my_table= obj.form_options['table'];
	var current_table=$("#current_table").val();// nome tabella attualmente salvata sul file (mi serve per bypassare il mio nome attuale dalla lista delle tabelle del visite_exams)
	var is_valid = Formbuilder.validators['validate/table_column_name_valid'](obj,current,my_table,true);//my_table != '' &&  my_table.length <=20 && !/^\d/.test(my_table) && $.inArray(my_table,Formbuilder.utils.oracle_reserved_words)<0 ? true : false;
	/*if(is_valid){
		var tables=JSON.parse($("#structure_db_tables").val());
		jQuery.each(tables,function(table){
			if(is_valid && current_table!=table && table !== 'null' && table==my_table ){
					//is_valid=false;
					validation_confirmation_messages+="<li>Table name already used! Are you sure to use an existing table in this form?</li>";
					validation_messages+="<li><span class='warning'>Table name already used! Are you sure to use an existing table in this form?</span></li>";
			}
		});
	}
	else if (my_table.length > 20){
		validation_messages+="<li>The table name can't exceed 20 characters!</li>";
	}
	else if ( /^\d/.test(my_table)){
		validation_messages+="<li>The table name can't start with a numeric character!</li>";
	}
	else if ( $.inArray(my_table,Formbuilder.utils.oracle_reserved_words)>=0){
			validation_messages+="<li>This table name can't be used because it is a reserved word!</li>";
			
	}
	else{
		validation_messages+="<li>The table name must be specified!</li>";
	}*/
	if(!is_valid){
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TABLE )) == null ? '' : __t) + "']").css("border", "1px solid red");
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TABLE )) == null ? '' : __t) + "']").parent().parent().css("border", "1px solid red");
	}
	else{
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TABLE )) == null ? '' : __t) + "']").css("border","");
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TABLE )) == null ? '' : __t) + "']").parent().parent().css("border","");
		current_table=$("#current_table").val(obj.form_options['table']);
	}
	return is_valid ;
};
this["Formbuilder"]["validators"]["validate/form_links"] = function(obj,current) {
	//alert("CIAO");
	var is_valid = obj.form_options['link_to'] != '' ? true : false;
	if(!is_valid){
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.LINK_TO )) == null ? '' : __t) + "']").css("border", "1px solid red");
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.LINK_TO )) == null ? '' : __t) + "']").parent().parent().parent().css("border", "1px solid red");
		validation_messages+="<li> Redirecting links to after saving the form bust be specified, default link to the patient's view has been restored</li>";
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.LINK_TO )) == null ? '' : __t) + "']").val("index.php?CENTER=[CENTER]|and|CODPAT=[CODPAT]|and|exams=visite_exams.xml");
		fb.mainView.editView.model.attributes.form_options.link_to="index.php?CENTER=[CENTER]|and|CODPAT=[CODPAT]|and|exams=visite_exams.xml";
	}
	else{
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.LINK_TO )) == null ? '' : __t) + "']").css("border","");
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.LINK_TO )) == null ? '' : __t) + "']").parent().parent().parent().css("border","");
	}
	return is_valid ;
};

this["Formbuilder"]["validators"]["validate/form_main_sub"] = function(obj,current) {
	//alert("CIAO");
	var is_valid = false;
	if(obj.form_options['is_main']||$('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked')){
		//è main
		if ( ( obj.form_options['main_field'] != "" && Formbuilder.validators['validate/table_column_name_valid'](obj,current,obj.form_options['main_field'],false) && obj.form_options['main_field_value'] != "" && obj.form_options['table_sub'] != "" && Formbuilder.validators['validate/table_column_name_valid'](obj,current,obj.form_options['table_sub'],false)) )
		{
			is_valid=true;
			if(current){
				$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.MAIN_FIELD )) == null ? '' : __t) + "']").val($("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.MAIN_FIELD )) == null ? '' : __t) + "']").val().toUpperCase().trim().replace(/ /g, "").replace(/\W/g, "").replace($("#study_prefix").val()+"_",""));
				$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TABLE_SUB )) == null ? '' : __t) + "']").val($("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TABLE_SUB )) == null ? '' : __t) + "']").val().toUpperCase().trim().replace(/ /g, "").replace(/\W/g, "").replace($("#study_prefix").val()+"_",""));
			}
		}
		else{
			is_valid=false;
		}
	}
	else{
		if( ( obj.form_options['field_tb_show'] != '' && obj.form_options['tb_header'] != '' ) ||
			( obj.form_options['field_tb_show'] == '' && obj.form_options['tb_header'] == '' ) )
		{
			is_valid=true;
		}
	}
	
	if(!is_valid){
		if($('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked') && (obj.form_options['main_field']=="" || !Formbuilder.validators['validate/table_column_name_valid'](obj,current,obj.form_options['main_field'],false))){
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.MAIN_FIELD )) == null ? '' : __t) + "']").css("border", "1px solid red");
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.MAIN_FIELD )) == null ? '' : __t) + "']").parent().parent().parent().css("border", "1px solid red");
		}
		if($('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked') && obj.form_options['main_field_value']==""){
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.MAIN_FIELD_VALUE )) == null ? '' : __t) + "']").css("border", "1px solid red");
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.MAIN_FIELD_VALUE )) == null ? '' : __t) + "']").parent().parent().parent().css("border", "1px solid red");
		}
		if($('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked') && (obj.form_options['table_sub']=="" || !Formbuilder.validators['validate/table_column_name_valid'](obj,current,obj.form_options['table_sub'],false))){
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TABLE_SUB )) == null ? '' : __t) + "']").css("border", "1px solid red");
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TABLE_SUB )) == null ? '' : __t) + "']").parent().parent().parent().css("border", "1px solid red");
		}
		if(!$('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked') && obj.form_options['field_tb_show']==""){
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.FIELD_TB_SHOW )) == null ? '' : __t) + "']").css("border", "1px solid red");
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.FIELD_TB_SHOW )) == null ? '' : __t) + "']").parent().parent().parent().css("border", "1px solid red");
		}
		if(!$('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked') && obj.form_options['tb_header']==""){
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TB_HEADER )) == null ? '' : __t) + "']").css("border", "1px solid red");
			$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TB_HEADER )) == null ? '' : __t) + "']").parent().parent().parent().css("border", "1px solid red");
		}
		
	}
	else{
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.MAIN_FIELD )) == null ? '' : __t) + "']").css("border","");
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.MAIN_FIELD_VALUE )) == null ? '' : __t) + "']").css("border","");
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TABLE_SUB )) == null ? '' : __t) + "']").css("border","");
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.FIELD_TB_SHOW )) == null ? '' : __t) + "']").css("border","");
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.TB_HEADER	 )) == null ? '' : __t) + "']").css("border","");
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.MAIN_FIELD )) == null ? '' : __t) + "']").parent().parent().parent().css("border","");
	}
	return is_valid ;
};

this["Formbuilder"]["validators"]["validate/form_buttons"] = function(obj,current) {
	var is_valid = true;
	if(!obj.show_save && !obj.show_send){
		is_valid = false;
		validation_messages+="<li> At least one button between \"Save\" and \"Send\" must be checked.</li>";
		$("input[data-rv-checked='model." + (( __t = (Formbuilder.options.mappings.SHOW_SAVE_BUTTON )) == null ? '' : __t) + "']").parent().parent().parent().parent().css("border", "1px solid red");
	}
	else{
		
		$("input[data-rv-checked='model." + (( __t = (Formbuilder.options.mappings.SHOW_SAVE_BUTTON )) == null ? '' : __t) + "']").parent().parent().parent().parent().css("border", "");
	}
	return is_valid;
};


//VALIDAZIONE ATTRIBUTI TEXTBOX
this["Formbuilder"]["validators"]["validate/textbox"] = function(obj,current) {
	//alert("CIAO");
	var valid;
	if($('#field_view_'+obj.cid).attr('class').indexOf('editing') >= 0 ){ 
		//SE HO CURRENT=FALSE ALLORA STO FACENDO LA VALIDAZIONE DI TUTTI I FIELDS MA SE IL MIO FIELD E' IN EDITING 
		//ALLORA CURRENT DIVENTA TRUE per VISUALIZZARE GLI EVENTUALI ERORRI
		current=true;
	}
	valid_db_info = Formbuilder.validators['validate/db_info'](obj,current);  
	valid_bytb = Formbuilder.validators['validate/bytb'](obj,current);
	valid_condition = Formbuilder.validators['validate/condition'](obj,current);
	allowed_values = Formbuilder.validators['validate/allowed_values'](obj,current);
	
	valid=valid_db_info && valid_bytb && valid_condition && allowed_values;
	if(!valid){
		$('#field_view_'+obj.cid).addClass('error');
		if(validation_messages!=="" && current){
			bootbox.dialog({
						message : "<ul>"+validation_messages+"</ul>",
						title : 'Validating Form',
						className : "structLoader"});
			validation_messages="";
		}
	}
	else{
		if(validation_confirmation_messages!=="" && current){
					bootbox.alert({
							message : "<ul>"+validation_confirmation_messages+"</ul>",
							title : 'Validating Form',
							className : "structLoader",
							});
							validation_confirmation_messages="";
				}
		$('#field_view_'+obj.cid).removeClass('error');
		
	}
	return valid;
};

//VALIDAZIONE ATTRIBUTI LABEL
this["Formbuilder"]["validators"]["validate/text"] = function(obj,current) {
	//alert("CIAO");
	var valid;
	if($('#field_view_'+obj.cid).attr('class').indexOf('editing') >= 0 ){ 
		//SE HO CURRENT=FALSE ALLORA STO FACENDO LA VALIDAZIONE DI TUTTI I FIELDS MA SE IL MIO FIELD E' IN EDITING 
		//ALLORA CURRENT DIVENTA TRUE per VISUALIZZARE GLI EVENTUALI ERORRI
		current=true;
	}
	if(current && obj.field_type==="text" && ($("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").val()===undefined|| $("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").val()=="")){
		$("input[data-rv-input='model." + (( __t = (Formbuilder.options.mappings.VAR )) == null ? '' : __t) + "']").val("_labelfield");
		$("input[data-rv-checked='model." + (( __t = (Formbuilder.options.mappings.TB )) == null ? '' : __t) + "']").prop("checked",true);
	}
	if(current && obj.field_type==="text"){
		$("input[data-rv-checked='model." + (( __t = (Formbuilder.options.mappings.TB )) == null ? '' : __t) + "']").prop("checked",true); //le label devono sempre essere TBNO!
	}
	valid_db_info = Formbuilder.validators['validate/db_info'](obj,current); // NON VALIDO IL DB_INFO PERCHE' per le label non c'e' bisogno (li inserisco solo per non far partire l'errore alla validazione con l'xsd lato server)  
	valid_bytb = Formbuilder.validators['validate/bytb'](obj,current);
	valid_condition = Formbuilder.validators['validate/condition'](obj,current);
	allowed_values = Formbuilder.validators['validate/allowed_values'](obj,current);
	
	valid=valid_db_info && valid_bytb && valid_condition && allowed_values;
	if(!valid){
		$('#field_view_'+obj.cid).addClass('error');
		if(validation_messages!=="" && current){
			bootbox.dialog({
						message : "<ul>"+validation_messages+"</ul>",
						title : 'Validating Form',
						className : "structLoader"});
			validation_messages="";
		}
	}
	else{
		if(validation_confirmation_messages!=="" && current){
					bootbox.alert({
							message : "<ul>"+validation_confirmation_messages+"</ul>",
							title : 'Validating Form',
							className : "structLoader",
							});
							validation_confirmation_messages="";
				}
		$('#field_view_'+obj.cid).removeClass('error');
		
	}
	return valid;
};

//VALIDAZIONE ATTRIBUTI ORA
this["Formbuilder"]["validators"]["validate/ora"] = function(obj,current) {
	//alert("CIAO");
	var valid;
	if($('#field_view_'+obj.cid).attr('class').indexOf('editing') >= 0 ){ 
		//SE HO CURRENT=FALSE ALLORA STO FACENDO LA VALIDAZIONE DI TUTTI I FIELDS MA SE IL MIO FIELD E' IN EDITING 
		//ALLORA CURRENT DIVENTA TRUE per VISUALIZZARE GLI EVENTUALI ERORRI
		current=true;
	}
	valid_db_info = Formbuilder.validators['validate/db_info'](obj,current);  
	valid_bytb = Formbuilder.validators['validate/bytb'](obj,current);
	valid_condition = Formbuilder.validators['validate/condition'](obj,current);
	//allowed_values = Formbuilder.validators['validate/allowed_values'](obj,current);
	
	valid=valid_db_info && valid_bytb && valid_condition;//&& allowed_values;
	if(!valid){
		$('#field_view_'+obj.cid).addClass('error');
		if(validation_messages!=="" && current){
			bootbox.dialog({
						message : "<ul>"+validation_messages+"</ul>",
						title : 'Validating Form',
						className : "structLoader"});
			validation_messages="";
		}
	}
	else{
		if(validation_confirmation_messages!=="" && current){
					bootbox.alert({
							message : "<ul>"+validation_confirmation_messages+"</ul>",
							title : 'Validating Form',
							className : "structLoader",
							});
							validation_confirmation_messages="";
				}
		$('#field_view_'+obj.cid).removeClass('error');
		
	}
	return valid;
};

//VALIDAZIONE ATTRIBUTI DATE_CAL
this["Formbuilder"]["validators"]["validate/date_cal"] = function(obj,current) {
	//alert("CIAO");
	var valid;
	if($('#field_view_'+obj.cid).attr('class').indexOf('editing') >= 0 ){ 
		//SE HO CURRENT=FALSE ALLORA STO FACENDO LA VALIDAZIONE DI TUTTI I FIELDS MA SE IL MIO FIELD E' IN EDITING 
		//ALLORA CURRENT DIVENTA TRUE per VISUALIZZARE GLI EVENTUALI ERORRI
		current=true;
	}
	valid_db_info = Formbuilder.validators['validate/db_info'](obj,current);  
	valid_bytb = Formbuilder.validators['validate/bytb'](obj,current);
	valid_condition = Formbuilder.validators['validate/condition'](obj,current);
	//allowed_values = Formbuilder.validators['validate/allowed_values'](obj,current);
	
	valid=valid_db_info && valid_bytb && valid_condition;//&& allowed_values;
	if(!valid){
		$('#field_view_'+obj.cid).addClass('error');
		if(validation_messages!=="" && current){
			bootbox.dialog({
						message : "<ul>"+validation_messages+"</ul>",
						title : 'Validating Form',
						className : "structLoader"});
			validation_messages="";
		}
	}
	else{
		if(validation_confirmation_messages!=="" && current){
					bootbox.alert({
							message : "<ul>"+validation_confirmation_messages+"</ul>",
							title : 'Validating Form',
							className : "structLoader",
							});
							validation_confirmation_messages="";
				}
		$('#field_view_'+obj.cid).removeClass('error');
		
	}
	return valid;
};
//VALIDAZIONE ATTRIBUTI TEXTAREA
this["Formbuilder"]["validators"]["validate/textarea"] = function(obj,current) {
	//alert("CIAO");
	var valid;
		//TODO GESTIRE UN UNICO ALERT CON I VARI MESSAGGI DI ERRORE (vedi bootbox.dialog in validate/form_name)
		if($('#field_view_'+obj.cid).attr('class').indexOf('editing') >= 0 ){ 
			//SE HO CURRENT=FALSE ALLORA STO FACENDO LA VALIDAZIONE DI TUTTI I FIELDS MA SE IL MIO FIELD E' IN EDITING 
			//ALLORA CURRENT DIVENTA TRUE per VISUALIZZARE GLI EVENTUALI ERORRI
			current=true;
		}
		valid_db_info = Formbuilder.validators['validate/db_info'](obj,current);  
		valid_bytb = Formbuilder.validators['validate/bytb'](obj,current);
		valid_condition = Formbuilder.validators['validate/condition'](obj,current);
		
		valid=valid_db_info && valid_bytb && valid_condition;
		if(!valid){
			$('#field_view_'+obj.cid).addClass('error');
			if(validation_messages!=="" && current){
				bootbox.dialog({
							message : "<ul>"+validation_messages+"</ul>",
							title : 'Validating Form',
							className : "structLoader"});
				validation_messages="";
			}
		}
		else{
			if(validation_confirmation_messages!=="" && current){
						bootbox.alert({
								message : "<ul>"+validation_confirmation_messages+"</ul>",
								title : 'Validating Form',
								className : "structLoader",
								});
								validation_confirmation_messages="";
					}
			$('#field_view_'+obj.cid).removeClass('error');
			
		}
	return valid;
};

//VALIDAZIONE ATTRIBUTI CHECKBOX
this["Formbuilder"]["validators"]["validate/checkbox"] = function(obj,current) {
	//alert("CIAO");
	var valid;
		//TODO GESTIRE UN UNICO ALERT CON I VARI MESSAGGI DI ERRORE (vedi bootbox.dialog in validate/form_name)
		if($('#field_view_'+obj.cid).attr('class').indexOf('editing') >= 0 ){ 
			//SE HO CURRENT=FALSE ALLORA STO FACENDO LA VALIDAZIONE DI TUTTI I FIELDS MA SE IL MIO FIELD E' IN EDITING 
			//ALLORA CURRENT DIVENTA TRUE per VISUALIZZARE GLI EVENTUALI ERORRI
			current=true;
		}
		valid_db_info = Formbuilder.validators['validate/db_info'](obj,current);  
		valid_bytb = Formbuilder.validators['validate/bytb'](obj,current);
		valid_condition = Formbuilder.validators['validate/condition'](obj,current);
		valid_values = Formbuilder.validators['validate/option_values'](obj,current);
		valid=valid_db_info && valid_bytb && valid_condition && valid_values;
		if(!valid){
			$('#field_view_'+obj.cid).addClass('error');
			if(validation_messages!=="" && current){
				bootbox.dialog({
							message : "<ul>"+validation_messages+"</ul>",
							title : 'Validating Form',
							className : "structLoader"});
				validation_messages="";
			}
		}
		else{
			if(validation_confirmation_messages!=="" && current){
						bootbox.alert({
								message : "<ul>"+validation_confirmation_messages+"</ul>",
								title : 'Validating Form',
								className : "structLoader",
								});
								validation_confirmation_messages="";
					}
			$('#field_view_'+obj.cid).removeClass('error');
			
		}
	return valid;
};
//VALIDAZIONE ATTRIBUTI RADIO
this["Formbuilder"]["validators"]["validate/radio"] = function(obj,current) {
	//alert("CIAO");
	var valid;
		//TODO GESTIRE UN UNICO ALERT CON I VARI MESSAGGI DI ERRORE (vedi bootbox.dialog in validate/form_name)
		if($('#field_view_'+obj.cid).attr('class').indexOf('editing') >= 0 ){ 
			//SE HO CURRENT=FALSE ALLORA STO FACENDO LA VALIDAZIONE DI TUTTI I FIELDS MA SE IL MIO FIELD E' IN EDITING 
			//ALLORA CURRENT DIVENTA TRUE per VISUALIZZARE GLI EVENTUALI ERORRI
			current=true;
		}
		valid_db_info = Formbuilder.validators['validate/db_info'](obj,current);  
		valid_bytb = Formbuilder.validators['validate/bytb'](obj,current);
		valid_condition = Formbuilder.validators['validate/condition'](obj,current);
		valid_values = Formbuilder.validators['validate/option_values'](obj,current);
		
		valid=valid_db_info && valid_bytb && valid_condition && valid_values;
		if(!valid){
			$('#field_view_'+obj.cid).addClass('error');
			if(validation_messages!=="" && current){
				bootbox.dialog({
							message : "<ul>"+validation_messages+"</ul>",
							title : 'Validating Form',
							className : "structLoader"});
				validation_messages="";
			}
		}
		else{
			if(validation_confirmation_messages!=="" && current){
						bootbox.alert({
								message : "<ul>"+validation_confirmation_messages+"</ul>",
								title : 'Validating Form',
								className : "structLoader",
								});
								validation_confirmation_messages="";
					}
			$('#field_view_'+obj.cid).removeClass('error');
			
		}
	return valid;
};
//VALIDAZIONE ATTRIBUTI SELECT
this["Formbuilder"]["validators"]["validate/select"] = function(obj,current) {
	//alert("CIAO");
	var valid;
		//TODO GESTIRE UN UNICO ALERT CON I VARI MESSAGGI DI ERRORE (vedi bootbox.dialog in validate/form_name)
		if($('#field_view_'+obj.cid).attr('class').indexOf('editing') >= 0 ){ 
			//SE HO CURRENT=FALSE ALLORA STO FACENDO LA VALIDAZIONE DI TUTTI I FIELDS MA SE IL MIO FIELD E' IN EDITING 
			//ALLORA CURRENT DIVENTA TRUE per VISUALIZZARE GLI EVENTUALI ERORRI
			current=true;
		}
		valid_db_info = Formbuilder.validators['validate/db_info'](obj,current);  
		valid_bytb = Formbuilder.validators['validate/bytb'](obj,current);
		valid_condition = Formbuilder.validators['validate/condition'](obj,current);
		valid_values = Formbuilder.validators['validate/option_values'](obj,current);
		
		valid=valid_db_info && valid_bytb && valid_condition && valid_values;
		if(!valid){
			$('#field_view_'+obj.cid).addClass('error');
			if(validation_messages!=="" && current){
				bootbox.dialog({
							message : "<ul>"+validation_messages+"</ul>",
							title : 'Validating Form',
							className : "structLoader"});
				validation_messages="";
			}
		}
		else{
			if(validation_confirmation_messages!=="" && current){
						bootbox.alert({
								message : "<ul>"+validation_confirmation_messages+"</ul>",
								title : 'Validating Form',
								className : "structLoader",
								});
								validation_confirmation_messages="";
					}
			$('#field_view_'+obj.cid).removeClass('error');
			
		}
	return valid;
};
//VALIDAZIONE ATTRIBUTI SELECT
this["Formbuilder"]["validators"]["validate/hidden"] = function(obj,current) {
	//alert("CIAO");
	var valid;
		//TODO GESTIRE UN UNICO ALERT CON I VARI MESSAGGI DI ERRORE (vedi bootbox.dialog in validate/form_name)
		if($('#field_view_'+obj.cid).attr('class').indexOf('editing') >= 0 ){ 
			//SE HO CURRENT=FALSE ALLORA STO FACENDO LA VALIDAZIONE DI TUTTI I FIELDS MA SE IL MIO FIELD E' IN EDITING 
			//ALLORA CURRENT DIVENTA TRUE per VISUALIZZARE GLI EVENTUALI ERORRI
			current=true;
		}
		valid_db_info = Formbuilder.validators['validate/db_info'](obj,current);  
		valid_bytb = Formbuilder.validators['validate/bytb'](obj,current);
		valid_default_value=Formbuilder.validators['validate/value'](obj,current);
		valid=valid_db_info && valid_bytb && valid_default_value;
		if(!valid){
			$('#field_view_'+obj.cid).addClass('error');
			if(validation_messages!=="" && current){
				bootbox.dialog({
							message : "<ul>"+validation_messages+"</ul>",
							title : 'Validating Form',
							className : "structLoader"});
				validation_messages="";
			}
		}
		else{
			if(validation_confirmation_messages!=="" && current){
				bootbox.alert({
						message : "<ul>"+validation_confirmation_messages+"</ul>",
						title : 'Validating Form',
						className : "structLoader",
						});
				validation_confirmation_messages="";
			}
			$('#field_view_'+obj.cid).removeClass('error');
			
		}
	return valid;
};
//EDIT ATTRIBUTI FORM
this["Formbuilder"]["templates"]["edit/form_name"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseFormName" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Form name'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseFormName" class="panel-collapse collapse" style="height: 0px;">'+
				'		<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.FNAME )) == null ? '' : __t) + '" style="width: 250px" />'+
				'	</div>'+
				'	</div>'+
				'	</div>';
		//__p += '<div class=\'fb-edit-section-header\'>Form title:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.TITOLO )) == null ? '' : __t) + '" />\n';
		
	}
	
	return __p;
};
this["Formbuilder"]["templates"]["edit/form_title"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseFormTitle" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Form title'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseFormTitle" class="panel-collapse collapse" style="height: 0px;">'+
				'		<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.TITOLO )) == null ? '' : __t) + '" style="width: 250px" />'+
				'	</div>'+
				'	</div>'+
				'	</div>';
		//__p += '<div class=\'fb-edit-section-header\'>Form title:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.TITOLO )) == null ? '' : __t) + '" />\n';
	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/form_table"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseDatabaseTable" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Database Table'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseDatabaseTable" class="panel-collapse collapse" style="height: 0px;">'+
				'		<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.TABLE )) == null ? '' : __t) + '" style="width: 250px" />'+
				'	</div>'+
				'	</div>'+
				'	</div>';
		//__p += '<div class=\'fb-edit-section-header\'>Database Table:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.TABLE )) == null ? '' : __t) + '" />\n';
	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/form_links"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseFormLinks" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Redirecting links to'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseFormLinks" class="panel-collapse collapse" style="height: 0px;">' +
				'		<div style="float:left">after saving<br/>the form</div><div style="float:right">\n<select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.LINK_TO )) == null ? '' : __t) + '"><option ></option></select></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">after sending<br/>the form</div><div style="float:right"><select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.LINK_TO_SEND )) == null ? '' : __t) + '"><option ></option></select></div>' +
				'		<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'	</div>';
		//__p += '<div class=\'fb-edit-section-header\'> Redirecting links to:';
		//__p += '<div>- after saving the form:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.LINK_TO )) == null ? '' : __t) + '" />\n';
		//__p += '<div>- after sending the form:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.LINK_TO_SEND )) == null ? '' : __t) + '" />\n';
		//__p += '</div>\n';
	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/form_f_to_calls"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseFormWorkFlow" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;WorkFlow function to call'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseFormWorkFlow" class="panel-collapse collapse" style="height: 0px;">' +
				'		<div style="float:left">after saving<br/>the form</div><div style="float:right">\n<select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.F_TO_CALL )) == null ? '' : __t) + '"><option ></option></select></div>' +
				'		<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'	</div>';
		//__p += '<div class=\'fb-edit-section-header\'> Redirecting links to:';
		//__p += '<div>- after saving the form:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.LINK_TO )) == null ? '' : __t) + '" />\n';
		//__p += '<div>- after sending the form:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.LINK_TO_SEND )) == null ? '' : __t) + '" />\n';
		//__p += '</div>\n';
	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/form_cols"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		//TODO: capire se ancora necessario questo campo (nel nuovo xmr dovrebbe non esistere più perchè la form viene creata con div e non con table?)
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseFormCols" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Columns number'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseFormCols" class="panel-collapse collapse" style="height: 0px;">' +
				'		<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.COLS )) == null ? '' : __t) + '" style="width: 50px"/>\n' +
				'	</div>'+
				'	</div>'+
				'	</div>';
		//__p += '<div class=\'fb-edit-section-header\'>Columns number:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.COLS )) == null ? '' : __t) + '" />\n';
	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/form_js_functions"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p +=  '	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseFormJSFunctions" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Javascript functions to call'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseFormJSFunctions" class="panel-collapse collapse" style="height: 0px;">' +
				'		<div style="float:left">On load event</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.LOAD )) == null ? '' : __t) + '" style="width: 250px"/></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Before saving</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.JS_FUNCTION )) == null ? '' : __t) + '" style="width: 250px"/></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Before sending</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.JS_ONSAVE )) == null ? '' : __t) + '" style="width: 250px"/></div>' +
				'		<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'	</div>';
		//__p += '<div class=\'fb-edit-section-header\'> Javascript functions to call:';
		//__p += '<div>- on load event:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.LOAD )) == null ? '' : __t) + '" />\n';
		//__p += '<div>- before saving:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.JS_FUNCTION )) == null ? '' : __t) + '" />\n';
		//__p += '<div>- before sending:</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.JS_ONSAVE )) == null ? '' : __t) + '" />\n';
		//__p += '</div>\n';
	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/form_main_sub"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += 	'	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseFormMainSub" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Main/Sub attributes'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseFormMainSub" class="panel-collapse collapse" style="height: 0px;">' +
				'		<div style="float:left"><label>\n  <input type=\'checkbox\' data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.IS_MAIN )) == null ? '' : __t) + '\' />\n&nbsp;\n</label>Is main form? <em>(left the fields blank if none of them)</em></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Main Field:</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.MAIN_FIELD )) == null ? '' : __t) + '" style="width: 250px"/></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Main Field Value:</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.MAIN_FIELD_VALUE )) == null ? '' : __t) + '" style="width: 250px"/></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Table sub:</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.TABLE_SUB )) == null ? '' : __t) + '" style="width: 250px"/></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Field Tb show:</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.FIELD_TB_SHOW )) == null ? '' : __t) + '" style="width: 250px"/></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left">Tb header:</div><div style="float:right"><input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.TB_HEADER )) == null ? '' : __t) + '" style="width: 250px"/></div>' +
				'		<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'	</div>'+
				'</div>';
	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/form_buttons"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += 	'	<div class="panel panel-default">'+
				'	<div class="panel-heading">'+
				'	<div class=\'fb-edit-section-header\'> '+
				'		<a href="#collapseFormButtons" data-parent="#accordion" data-toggle="collapse" class="accordion-toggle collapsed">'+
				'			&nbsp;Form Buttons'+
				'		</a>'+
				'	</div>'+
				'	<div id="collapseFormButtons" class="panel-collapse collapse" style="height: 0px;">' +
				'		<div style="float:left"><label>\n  <input type=\'checkbox\' onclick="if($(this).prop(\'checked\')&&$(\'input[data-rv-input=\\\'model.save\\\']\').val()==\'\'){$(\'input[data-rv-input=\\\'model.save\\\']\').val(\'Save\');fb.mainView.editView.model.attributes.save=\'Save\';}else{$(\'input[data-rv-input=\\\'model.save\\\']\').val(\'\');}" data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.SHOW_SAVE_BUTTON )) == null ? '' : __t) + '\' />\n&nbsp;\n</label>Save button:</div><div style="float:right"><input type="text" onchange="if($(\'input[data-rv-checked=\\\'model.show_save\\\']\').prop(\'checked\')&&$(this).val()==\'\'){$(this).val(\'Save\');}else{$(\'input[data-rv-checked=\\\'model.show_save\\\']\').prop(\'checked\',true);fb.mainView.editView.model.attributes.show_save=true;}"  data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.SAVE_BUTTON )) == null ? '' : __t) + '" style="width: 125px"/></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left"><label>\n  <input type=\'checkbox\' onclick="if($(this).prop(\'checked\')&&$(\'input[data-rv-input=\\\'model.send\\\']\').val()==\'\'){$(\'input[data-rv-input=\\\'model.send\\\']\').val(\'Send\');fb.mainView.editView.model.attributes.send=\'Send\';}else{$(\'input[data-rv-input=\\\'model.send\\\']\').val(\'\');}" data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.SHOW_SEND_BUTTON )) == null ? '' : __t) + '\' />\n&nbsp;\n</label>Send button:</div><div style="float:right"><input type="text" onchange="if($(\'input[data-rv-checked=\\\'model.show_send\\\']\').prop(\'checked\')&&$(this).val()==\'\'){$(this).val(\'Send\');}else{$(\'input[data-rv-checked=\\\'model.show_send\\\']\').prop(\'checked\',true);fb.mainView.editView.model.attributes.show_send=true;}" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.SEND_BUTTON )) == null ? '' : __t) + '" style="width: 125px"/></div>' +
				'		<div style="clear:both"></div>'+
				'		<div style="float:left"><label>\n  <input type=\'checkbox\' onclick="if($(this).prop(\'checked\')&&$(\'input[data-rv-input=\\\'model.cancel\\\']\').val()==\'\'){$(\'input[data-rv-input=\\\'model.cancel\\\']\').val(\'Cancel\');fb.mainView.editView.model.attributes.cancel=\'Cancel\';}else{$(\'input[data-rv-input=\\\'model.cancel\\\']\').val(\'\');}" data-rv-checked=\'model.' + (( __t = (Formbuilder.options.mappings.SHOW_CANCEL_BUTTON )) == null ? '' : __t) + '\' />\n&nbsp;\n</label>Cancel button:</div><div style="float:right"><input type="text" onchange="if($(\'input[data-rv-checked=\\\'model.show_cancel\\\']\').prop(\'checked\')&&$(this).val()==\'\'){$(this).val(\'Cancel\');}else{$(\'input[data-rv-checked=\\\'model.show_cancel\\\']\').prop(\'checked\',true);fb.mainView.editView.model.attributes.show_cancel=true;}" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.CANCEL_BUTTON )) == null ? '' : __t) + '" style="width: 125px"/></div>' +
				'		<div style="clear:both"></div>'+
				'	</div>'+
				'	</div>'+
				'</div>';
	}
	return __p;
};
this["Formbuilder"]["templates"]["MainChecked"]= function(){
		
		$('input[data-rv-input=\'model.form_options.main_field\']').prop('disabled',!$('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked'));
		$('input[data-rv-input=\'model.form_options.main_field\']').val(!$('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked') ? '' : $('input[data-rv-input=\'model.form_options.main_field\']').val());
		$('input[data-rv-input=\'model.form_options.main_field_value\']').prop('disabled',!$('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked'));
		$('input[data-rv-input=\'model.form_options.main_field_value\']').val(!$('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked') ? '' : $('input[data-rv-input=\'model.form_options.main_field_value\']').val());
		$('input[data-rv-input=\'model.form_options.table_sub\']').prop('disabled',!$('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked'));
		$('input[data-rv-input=\'model.form_options.table_sub\']').val(!$('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked') ? '' : $('input[data-rv-input=\'model.form_options.table_sub\']').val());
		
		$('input[data-rv-input=\'model.form_options.field_tb_show\']').prop('disabled',$('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked'));
		$('input[data-rv-input=\'model.form_options.field_tb_show\']').val($('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked') ? '' : $('input[data-rv-input=\'model.form_options.field_tb_show\']').val());
		$('input[data-rv-input=\'model.form_options.tb_header\']').prop('disabled',$('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked'));
		$('input[data-rv-input=\'model.form_options.tb_header\']').val($('input[data-rv-checked=\'model.form_options.is_main\']').prop('checked') ? '' : $('input[data-rv-input=\'model.form_options.tb_header\']').val());
			
}
/**
 *PERSONALIZZAZIONI XMR FORM BUILDER 
 * vmazzeo dsaraceno maggio 2014
 * END
*/
this["Formbuilder"]["templates"]["edit/size"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += '<div class=\'fb-edit-section-header\'>Size</div>\n<select data-rv-value="model.' + (( __t = (Formbuilder.options.mappings.SIZE )) == null ? '' : __t) + '">\n  <option value="small">Small</option>\n  <option value="medium">Medium</option>\n  <option value="large">Large</option>\n</select>\n';

	}
	return __p;
};

this["Formbuilder"]["templates"]["edit/units"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += '<div class=\'fb-edit-section-header\'>Units</div>\n<input type="text" data-rv-input="model.' + (( __t = (Formbuilder.options.mappings.UNITS )) == null ? '' : __t) + '" />\n';

	}
	return __p;
};

this["Formbuilder"]["templates"]["page"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += (( __t = ( Formbuilder.templates['partials/save_button']() )) == null ? '' : __t) + '\n' + (( __t = ( Formbuilder.templates['partials/left_side']() )) == null ? '' : __t) + '\n' + (( __t = ( Formbuilder.templates['partials/right_side']() )) == null ? '' : __t) + '\n<div class=\'fb-clear\'></div>';

	}
	return __p;
};

this["Formbuilder"]["templates"]["partials/add_field"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape, __j = Array.prototype.join;
	function print() {
		__p += __j.call(arguments, '');
	}

	with (obj) {
		__p += '<div class=\'fb-tab-pane active\' id=\'addField\'>\n  <div class=\'fb-add-field-types\'>\n    <div class=\'section\'>\n      ';
		_.each(_.sortBy(Formbuilder.inputFields, 'order'), function(f) { ;
			__p += '\n        <a data-field-type="' + (( __t = (f.field_type )) == null ? '' : __t) + '" class="' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '">\n          ' + (( __t = (f.addButton )) == null ? '' : __t) + '\n        </a>\n      ';
		});
		;
		__p += '\n    </div>\n\n    <div class=\'section\'>\n      ';
		_.each(_.sortBy(Formbuilder.nonInputFields, 'order'), function(f) { ;
			//NON FACCIO VISUALIZZARE I BOTTONI ADD/REMOVE IN CASO DI 'form'
			(f.field_type == 'form' || f.field_type == 'enable') ? '' : __p += '\n        <a data-field-type="' + (( __t = (f.field_type )) == null ? '' : __t) + '" class="' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '">\n          ' + (( __t = (f.addButton )) == null ? '' : __t) + '\n        </a>\n      ';
		});
		;
		__p += '\n    </div>\n  </div>\n</div>';

	}
	return __p;
};

this["Formbuilder"]["templates"]["partials/edit_field"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += '<div class=\'fb-tab-pane\' id=\'editField\'>\n  <div class=\'fb-edit-field-wrapper\'></div>\n</div>\n';

	}
	return __p;
};
this["Formbuilder"]["templates"]["partials/form_attributes"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += '<div class=\'fb-tab-pane\' id=\'formAttributes\'>\n  <div class=\'fb-edit-form-wrapper\'></div>\n</div>\n';

	}
	return __p;
};

this["Formbuilder"]["templates"]["partials/left_side"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += '<div class=\'fb-left\'>\n  <ul class=\'fb-tabs\'>\n    <li class=\'active\'><a data-target=\'#addField\'>Add new field</a></li>\n    <li><a data-target=\'#editField\'>Edit field</a></li>\n    <li><a data-target=\'#formAttributes\'>Form\nAttributes</a></li>\n  </ul>\n\n  <div class=\'fb-tab-content\'>\n    ' + (( __t = ( Formbuilder.templates['partials/add_field']() )) == null ? '' : __t) + '\n    ' + (( __t = ( Formbuilder.templates['partials/edit_field']() )) == null ? '' : __t)+ '\n    ' + (( __t = ( Formbuilder.templates['partials/form_attributes']() )) == null ? '' : __t) + '\n  </div>\n</div>';

	}
	return __p;
};

this["Formbuilder"]["templates"]["partials/right_side"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += '<div class=\'fb-right\'>\n  <div class=\'fb-no-response-fields\'>No response fields</div>\n  <div class=\'fb-response-fields\' style="margin-top:50px;"></div>\n</div>\n';

	}
	return __p;
};

this["Formbuilder"]["templates"]["partials/save_button"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		my_formname=location.href.substring(location.href.lastIndexOf("/")+1);
		__p += '<div class=\'fb-save-wrapper\'>\n'+
			   '<div style=\'float:left\'><h3>Building '+my_formname+'</h3></div>'+
			   '<div style=\'float:right\'><button class=\'js-save-form ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '\'></button>\n';
			   
		var my_location=location.href;
		__p += '&nbsp;<a href=\''+my_location+'/save/update_db\' class=\''+ (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) +'\'><i class=\'fa fa-database\'>&nbsp;</i>'+ (( __t = (Formbuilder.options.dict.UPDATE_DB_TABLE )) == null ? '' : __t) +'</a>';
		__p += '&nbsp;<a href=\''+my_location+'/save/drop_db\' class=\''+ (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) +'\'><i class=\'fa fa-database\'>&nbsp;</i>'+ (( __t = (Formbuilder.options.dict.DROP_DB_TABLE )) == null ? '' : __t) +'</a>';
		my_location=my_location.replace(/buildForm/g, 'editForm');
		__p += '&nbsp;<a href=\''+my_location+'\' class=\''+ (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) +'\'><i class=\'fa fa-file-text-o\'>&nbsp;</i>'+ (( __t = (Formbuilder.options.dict.EDIT_FORM_XML )) == null ? '' : __t) +'</a>'+
			   '</div>'+
			   '</div>'+
			   '<div style=\'clear:both;\'></div>';

	}
	return __p;
};

this["Formbuilder"]["templates"]["view/base"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += '<div class=\'subtemplate-wrapper\'>\n  <div class=\'cover\'></div>\n  ' + (( __t = ( Formbuilder.templates['view/label']({
				rf : rf
			}) )) == null ? '' : __t) + '\n\n  ' + (( __t = ( Formbuilder.fields[rf.get(Formbuilder.options.mappings.FIELD_TYPE)].view({
				rf : rf
			}) )) == null ? '' : __t) + '\n\n  ' + (( __t = ( Formbuilder.templates['view/description']({
				rf : rf
			}) )) == null ? '' : __t) + '\n  ' + (( __t = ( Formbuilder.templates['view/duplicate_remove']({
				rf : rf
			}) )) == null ? '' : __t) + '\n</div>\n';

	}
	return __p;
};

this["Formbuilder"]["templates"]["view/base_non_input"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += '<div class=\'subtemplate-wrapper\'>\n  <div class=\'cover\'></div>\n  ' + (( __t = ( Formbuilder.fields[rf.get(Formbuilder.options.mappings.FIELD_TYPE)].view({
				rf : rf
		}) )) == null ? '' : __t) + '\n  ' + ((rf.get(Formbuilder.options.mappings.FIELD_TYPE)) == 'form' || ((rf.get(Formbuilder.options.mappings.FIELD_TYPE)) == 'enable') ? '' : ( __t = ( Formbuilder.templates['view/duplicate_remove']({ //NON FACCIO VISUALIZZARE I BOTTONI ADD/REMOVE IN CASO DI 'form'
				rf : rf
			}) )) == null ? '' : __t) + '\n</div>\n';

	}
	return __p;
};

this["Formbuilder"]["templates"]["view/description"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		__p += '<span class=\'help-block\'>\n  ' + (( __t = ( Formbuilder.helpers.simple_format(rf.get(Formbuilder.options.mappings.DESCRIPTION)) )) == null ? '' : __t) + '\n</span>\n';
	}
	return __p;
};

this["Formbuilder"]["templates"]["view/duplicate_remove"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape;
	with (obj) {
		// VMAZZEO 09.05.2015 DISABILITO CLONAZIONE PER BUG DA RISOLVERE SUCCESSIVAMENTE ALLA VALIDAZIONE (la clonazione avviene per riferimento e non crea un nuovo oggetto field)
		//__p += '<div class=\'actions-wrapper\'>\n  <a class="js-duplicate ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Duplicate Field"><i class=\'fa fa-plus-circle\'></i></a>\n  <a class="js-clear ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Remove Field"><i class=\'fa fa-minus-circle\'></i></a>\n</div>';
		__p += '<div class=\'actions-wrapper\'>\n  <a class="js-clear ' + (( __t = (Formbuilder.options.BUTTON_CLASS )) == null ? '' : __t) + '" title="Remove Field"><i class=\'fa fa-minus-circle\'></i></a>\n</div>';

	}
	return __p;
};

this["Formbuilder"]["templates"]["view/label"] = function(obj) {
	obj || ( obj = {});
	var __t, __p = '', __e = _.escape, __j = Array.prototype.join;
	function print() {
		__p += __j.call(arguments, '');
	}

	with (obj) {
		//__p += '<label>\n  <span>' + (( __t = ( Formbuilder.helpers.simple_format(rf.get(Formbuilder.options.mappings.LABEL)) )) == null ? '' : __t) + '\n  ';
		if (rf.get(Formbuilder.options.mappings.PK)) { ;
			//__p += '\n    <abbr title=\'required\'><span class=\'fa fa-star\'></span> PRIMARY KEY </abbr>\n  ';
		} ;
		//__p += '\n</label>\n';

	}
	return __p;
};
