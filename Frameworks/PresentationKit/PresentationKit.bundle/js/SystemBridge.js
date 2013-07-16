// JavaScript library for more easily accessing the native
// framework commands from html content pages
var SystemBridge = (function(){

    var emptyArray = [], 
        slice = emptyArray.slice

    function isObject(obj) {
        return typeof obj === "object";
    }

    function empty() {
    }

    function param(obj, prefix) {
        var str = [];
        for (var p in obj) {
            var k = prefix ? prefix + "[" + p + "]" : p, 
            v = obj[p];
            str.push(isObject(v) ? param(v, k) : (k) + "=" + encodeURIComponent(v));
        }
        return str.join("&");
    }

    function extend(target) {
        if (target == undefined)
            target = this;
        if (arguments.length === 1) {
            for (var key in target)
                this[key] = target[key];
            return this;
        } else {
            slice.call(arguments, 1).forEach(function(source) {
                for (var key in source)
                    target[key] = source[key];
            });
        }
        return target;
    }

    var ajaxSettings = {
        type: 'GET',
        beforeSend: empty,
        context: undefined,
        timeout: 0,
    }

    function ajax(opts) {
        var xhr;
        try {

            var settings = opts || {};
            for (var key in ajaxSettings) {
                if (typeof (settings[key]) == 'undefined')
                    settings[key] = ajaxSettings[key];
            }

            if (!settings.url)
                settings.url = window.location;
            if (!settings.contentType)
                settings.contentType = "application/x-www-form-urlencoded";
            if (!settings.headers)
                settings.headers = {};

            if (!('async' in settings) || settings.async !== false)
                settings.async = true;

            if (!settings.dataType)
                settings.dataType = "text/html";
            else {
                switch (settings.dataType) {
                    case "script":
                        settings.dataType = 'text/javascript, application/javascript';
                        break;
                    case "json":
                        settings.dataType = 'application/json';
                        break;
                    case "xml":
                        settings.dataType = 'application/xml, text/xml';
                        break;
                    case "html":
                        settings.dataType = 'text/html';
                        break;
                    case "text":
                        settings.dataType = 'text/plain';
                        break;
                    default:
                        settings.dataType = "text/html";
                        break;
                }
            }
            if (isObject(settings.data))
                settings.data = param(settings.data);
            if (settings.type.toLowerCase() === "get" && settings.data) {
                if (settings.url.indexOf("?") === -1)
                    settings.url += "?" + settings.data;
                else
                    settings.url += "&" + settings.data;
            }

            if (settings.crossDomain === null) settings.crossDomain = /^([\w-]+:)?\/\/([^\/]+)/.test(settings.url) &&
                    RegExp.$2 != window.location.host;

            if (!settings.crossDomain)
                settings.headers = extend({
                    'X-Requested-With': 'XMLHttpRequest'
                }, settings.headers);
            var abortTimeout;
            var context = settings.context;
            var protocol = /^([\w-]+:)\/\//.test(settings.url) ? RegExp.$1 : window.location.protocol;

            //ok, we are really using xhr
            xhr = new window.XMLHttpRequest();
            var dones = []
            var fails = []
            var always = []

            xhr.onreadystatechange = function () {
                var mime = settings.dataType;
                if (xhr.readyState === 4) {
                    clearTimeout(abortTimeout);
                    var result, error = false;
                    if ((xhr.status >= 200 && xhr.status < 300) || xhr.status === 0 && protocol == 'file:') {
                        if (mime === 'application/json' && !(/^\s*$/.test(xhr.responseText))) {
                            try {
                                result = JSON.parse(xhr.responseText);
                            } catch (e) {
                                error = e;
                            }
                        } else if (mime === 'application/xml, text/xml') {
                            result = xhr.responseXML;
                        } else {
                            result = xhr.responseText;
                        }
                        //If we're looking at a local file, we assume that no response sent back means there was an error
                        if (xhr.status === 0 && result.length === 0)
                            error = true;
                        if (error) {
                            fails.forEach(function(f){ f.call(context, xhr, 'parsererror', error) })
                        } else {
                            dones.forEach(function(d){ d.call(context, result, 'success', xhr) })
                        }
                    } else {
                        error = true;
                        fails.forEach(function(f){ f.call(context, xhr, 'error') })
                    }
                    always.forEach(function(a){ a.call(context, xhr, error ? 'error' : 'success') })
                }
            };
            xhr.open(settings.type, settings.url, settings.async);
            if (settings.withCredentials) xhr.withCredentials = true;

            if (settings.contentType)
                settings.headers['Content-Type'] = settings.contentType;
            for (var name in settings.headers)
                xhr.setRequestHeader(name, settings.headers[name]);
            if (settings.beforeSend.call(context, xhr, settings) === false) {
                xhr.abort();
                return false;
            }

            if (settings.timeout > 0)
                abortTimeout = setTimeout(function () {
                    xhr.onreadystatechange = empty;
                    xhr.abort();
                    settings.error.call(context, xhr, 'timeout');
                }, settings.timeout);
            xhr.send(settings.data);
        } catch (e) {
            // General errors (e.g. access denied) should also be sent to the error callback
            console.log(e);
            settings.error.call(context, xhr, 'error', e);
        }
        return {
            done: function(f) {
                dones.push(f)
                return this
            },
            fail: function(f) {
                fails.push(f)
                return this
            },
            always: function(f) {
                always.push(f)
                return this
            }
        }
    }

    /*******************************************************************************/

    function relativeToAbsolutePath(relPath) {
        var baseUri = new URI(location.href);
        var relUri = new URI(relPath);
        var relUriFull = relUri.resolve(baseUri);
        return encodeURI(relUriFull.toString());
    }

    function executeSystemCommand(method, data, responseType) {
        return ajax({
            url: 'http://system-bridge/' + method,
            type: 'POST',
            dataType: responseType != undefined ? responseType : 'json',
            data: JSON.stringify(data)
        })
    }

    return {
        loadResourceForPackage: function(package, resource) {
            return executeSystemCommand('loadResourceForPackage', {
                package: package,
                resource: resource
            }, 'xml')
        },

                    
        //-----------------------------
        // Supplemental Media Viewers
        //-----------------------------

        launchFullscreenVideo: function(url, trackingMessage) {
            return executeSystemCommand('launchFullScreenVideo', {
                url: relativeToAbsolutePath(url),
                trackingMessage: trackingMessage
            })
        },

        launchPDFViewer: function(url, title, trackingMessage) {
            return executeSystemCommand('launchPDFViewer', {
                url: relativeToAbsolutePath(url),
                title: title,
                trackingMessage: trackingMessage
            })
        },

        launchPDFViewerAtPage: function(url, title, pageNum, trackingMessage) {
            return executeSystemCommand('launchPDFViewer', {
                url: relativeToAbsolutePath(url),
                title: title,
                page: pageNum,
                trackingMessage: trackingMessage
            })
        },

        launchFullscreenWebViewer: function(url, title, trackingMessage) {
            return executeSystemCommand('launchFullscreenWebViewer', {
                url: relativeToAbsolutePath(url),
                title: title,
                trackingMessage: trackingMessage
            })
        },

        launchExternalURL: function(url, trackingMessage) {
            return executeSystemCommand('launchExternalURL', {
                url: relativeToAbsolutePath(url),
                trackingMessage: trackingMessage
            })
        },

        launchPopUp: function(url, trackingMessage) {
            return executeSystemCommand('launchPopUp', {
                url: relativeToAbsolutePath(url),
                trackingMessage: trackingMessage
            })
        },

        closeTopPopUp : function() {
            return executeSystemCommand('closeTopPopUp')
        },


        //-----------------------------
        // Data Storage / Access
        //-----------------------------

        setSessionValue : function(key, value) {
            return executeSystemCommand('setValue', {
                durability: "session",
                key: key,
                value: value
            })
        },

        requestSessionValue: function(key, callback_name) {
            r = executeSystemCommand('getValue', {
                durability: "session",
                key: key
            })
            if (callback_name) {
                r.done(function(v) {
                    window[callback_name](v.value)
                })
            }
            return r
        },
         
        setPersistentValue: function(key, value) {
            return executeSystemCommand('setValue', {
                durability: "persistent",
                key: key,
                value: value
            })
        },

        requestPersistentValue: function(key, callback_name) {
            r = executeSystemCommand('getValue', {
                durability: "persistent",
                key: key
            })
            if (callback_name) {
                r.done(function(v) {
                    window[callback_name](v.value)
                })
            }
            return r
        },

        //-----------------------------
        // Navigation
        //-----------------------------

        goToSlide : function(slide) {
            return executeSystemCommand('goToSlide', {
                slide: slide
            })
        },

        goToAlternateCall : function(call, slide) {
            return executeSystemCommand('alternateCall', {
                call: call,
                slide: slide
            })
        },

        slideToLeftPage: function(slide) {
            return executeSystemCommand('slide', {
                direction: "left"
            })
        },

        slideToRightPage: function(slide) {
            return executeSystemCommand('slide', {
                direction: "right"
            })
        },

        slideToAbovePage: function(slide) {
            return executeSystemCommand('slide', {
                direction: "up"
            })
        },

        slideToBelowPage: function(slide) {
            return executeSystemCommand('slide', {
                direction: "down"
            })
        },

        enableSwipeToPage: function() {
            return executeSystemCommand('setSwipeToPageEnabled', {
                enabled: true
            })
        },

        disableSwipeToPage: function() {
            return executeSystemCommand('setSwipeToPageEnabled', {
                enabled: false
            })
        },

        pageLoadComplete: function() {
            return executeSystemCommand('pageLoadComplete')
        },

        //-----------------------------
        // Tracking
        //-----------------------------

        trackEvent: function(title, message, data) {
            return executeSystemCommand('trackEvent', {
                title: title,
                message: message,
                data: data
            })
        },

        submitSurveyResponse : function(survey, question, answer) {
            return executeSystemCommand('submitAnswerForSurveyQuestion', {
                survey: survey,
                question: question,
                answer: answer
            });
        },
                    
        submitSurvey : function(survey) {
            return executeSystemCommand('submitSurvey', {
                survey: survey
            });
        },

        //-----------------------------
        // Navigation Layer
        //-----------------------------

        setViewFrame: function(viewName, xPos, yPos, width, height, animated) {
            return executeSystemCommand('setViewFrame', {
                name: viewName,
                xPos: xPos,
                yPos: yPos,
                width: width,
                height: height,
                animated: animated
            })
        },
         
        setViewProperties: function(properties) {
            return executeSystemCommand('setViewProperties', {
                properties: properties
            })
        },
         
        //-----------------------------
        // Utility
        //-----------------------------

        requestCurrentSlideInfo: function(callback_name) {
            r = executeSystemCommand('requestCurrentSlideInfo')
            if (callback_name) {
                r.done(function(v) {
                    window[callback_name](v)
                })
            }
            return r
        },
					
		requestSFADetails: function() {
            return executeSystemCommand('requestSFADetails')
        },

          // display an alert box
        alert: function(title, message, button) {
            return executeSystemCommand('alert', {
                title: title,
                message: message,
                button: button
            })
        },
     }
})()


//----------------------------------------------------------------------------
// An URI datatype.  Based upon examples in RFC3986.
//
// js-uri <http://code.google.com/p/js-uri/>
//
// Dominic Mitchell <dom [at] happygiraffe.net>
//----------------------------------------------------------------------------

// Constructor for the URI object.
// Parse a string into its components.
var URI = function(str)
{
	if (!str)
		str = "";

	// Based on the regex in RFC2396 Appendix B.
	var parser = /^(?:([^:\/?\#]+):)?(?:\/\/([^\/?\#]*))?([^?\#]*)(?:\?([^\#]*))?(?:\#(.*))?/;
	var result = str.match(parser);
	this.scheme    = result[1] || null;
	this.authority = result[2] || null;
	this.path      = result[3] || null;
	this.query     = result[4] || null;
	this.fragment  = result[5] || null;
};

URI.prototype.toString = function ()
{
	var result = "";
	
    if (this.scheme) {
		result += this.scheme + ":";
    }
    
	if (this.authority) {
		result += "//" + this.authority;
    }
    
	if (this.path) {
		result += this.path;
    }
    
	if (this.query) {
		result += "?" + this.query;
    }
	
    if (this.fragment) {
		result += "#" + this.fragment;
    }
    
	return result;
};

// Introduce a new scope to define some private helper functions.
(function ()
{
	// RFC3986 §5.2.3 (Merge Paths)
	function merge(base, rel_path)
	{
		var dirname = /^(.*)\//;
 
        if (base.authority && !base.path) {
			return "/" + rel_path;
        }
		
 		return base.path.match(dirname)[0] + rel_path;
	}

	// Match two path segments, where the second is ".." 
	// and the first must not be "..".
	var DoubleDot = /\/((?!\.\.\/)[^\/]*)\/\.\.\//;

	function remove_dot_segments(path)
    {
        if (!path) {
			return "";
        }

		// Remove any single dots
		var newpath = path.replace(/\/\.\//g, '/');

		// Remove any trailing single dots.
		newpath = newpath.replace(/\/\.$/, '/');

		// Remove any double dots and the path previous.  NB: We can't use
		// the "g", modifier because we are changing the string that we're
		// matching over.
        while (newpath.match(DoubleDot)) {
			newpath = newpath.replace(DoubleDot, '/');
        }

		// Remove any trailing double dots.
		newpath = newpath.replace(/\/([^\/]*)\/\.\.$/, '/');

		// If there are any remaining double dot bits, then they're wrong
		// and must be nuked.  Again, we can't use the g modifier.
		while (newpath.match(/\/\.\.\//)) {
			newpath = newpath.replace(/\/\.\.\//, '/');
        }
                                      
		return newpath;
	}

	// RFC3986 §5.2.2. Transform References;
	URI.prototype.resolve = function (base)
	{
		var target = new URI();
		if (this.scheme) {
			target.scheme    = this.scheme;
			target.authority = this.authority;
			target.path      = remove_dot_segments(this.path);
			target.query     = this.query;
		} else {
			if (this.authority) {
				target.authority = this.authority;
				target.path      = remove_dot_segments(this.path);
				target.query     = this.query;
            } else {
				// XXX Original spec says "if defined and empty"…;
				if (!this.path) {
					target.path = base.path;
                    if (this.query) {
						target.query = this.query;
                    } else {
						target.query = base.query;
                    }
                } else {
					if (this.path.charAt(0) === '/') {
						target.path = remove_dot_segments(this.path);
                    } else {
						target.path = merge(base, this.path);
						target.path = remove_dot_segments(target.path);
                    }
					target.query = this.query;
                }
				target.authority = base.authority;
			}
			target.scheme = base.scheme;
		}
		target.fragment = this.fragment;
		return target;
	};

	URI.prototype.getQueryValue = function (variable)
	{
		var vars = this.query.split("&"); 
		for (i = 0; i < vars.length; i++) {
			var pair = vars[i].split("="); 
            if (pair[0] == variable) {
				return pair[1]; 
			}
        }
    };
})();
