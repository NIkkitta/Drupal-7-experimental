(function($) {

    Drupal.behaviors.restapi = {
        attach: function(context, settings) {
            function loadNode() {

            }
            loadNode();
            $('#load').click(function() {
                var val = $('#nodeid').val();
                console.log(val);
                if (val) {
                    alert(val);
                    $.ajax({
                        url: base_url + '/pluto/restapi/' + val,
                    });
                }

            })

        }
    };

})(jQuery);
