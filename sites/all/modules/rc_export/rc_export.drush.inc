<?php

/**
 * @file
 *   Drush support for node_export.
 */

/**
 * Implements hook_drush_command().
 */
function rc_export_drush_command() {
    $items['rc-node-export-export'] = array(
        'callback' => 'rc_node_export_callback_export',
        'description' => "Export nodes using Node export.",
        'arguments' => array(
            'nids' => "A list of space-separated node IDs to export.",
        ),
        'options' => array(
            'file' => "The filename of the output file.  If supplied, the node code will be exported to that file, otherwise it will export to stdout.",
            'format' => "If supplied, node code will be output using a particular export format, if available. (e.g. serialize)",
            'status' => "Filter for 'status'; A boolean value (0 or 1) indicating whether the node is published (visible to non-administrators).",
            'promote' => "Filter for 'promote'; A boolean value (0 or 1) indicating whether the node should be displayed on the front page.",
            'sticky' => "Filter for 'sticky'; A boolean value (0 or 1) indicating whether the node should be displayed at the top of lists in which it appears.",
            'translate' => "Filter for 'translate'; A boolean value (0 or 1) indicating whether the node translation needs to be updated.",
            'language' => "Filter for 'language'; The language code (e.g. de or en-US) of this node.",
            'type' => "Filter for 'type'; The machine-readable name (e.g. story or page) of the type of this node.",
            'sql' => "Filter by SQL (EXPERIMENTAL); An SQL query string that returns nids (e.g. \"SELECT nid FROM nodes WHERE nid < 10\").",
            'code' => "Filter by PHP code (EXPERIMENTAL); PHP code that prints or returns, an array or CSV string of nids (e.g. \"custom_get_my_nids();\"). Don't include PHP tags.",
            'og' => 'Filte by OG group',
        ),
        'examples' => array(
            'drush node-export-export 45 46 47 --file=filename' =>
            "export nodes with node IDs 45, 46, and 47 to the file with the supplied filename.",
            'drush node-export-export --type=story,page --file=filename' =>
            "export nodes of type story and page to the file with the supplied filename.",
        ),
    );


    // Add aliases for usability.
      rc_export_drush_command_add_alias($items, 'rc-node-export-export', 'rc-ne-export');


    return $items;
}


/**
 * A function to help alias commands as other commands.
 */
function rc_export_drush_command_add_alias(&$items, $command, $alias) {
    // Create a property on the command for adding aliases, if not there.
    if (!isset($items[$command]['rc_export command aliases'])) {
        $items[$command]['rc_export command aliases'] = array();
    }
    // Record the alias into that property.
    $items[$command]['rc_export command aliases'][] = $alias;
    // Create the alias as a new command.
    $items[$alias] = $items[$command];
    // Indicate what this new command is an alias for.
    $items[$alias]['rc_export alias for'] = $command;
}


/**
 * Drush command callback.
 *
 * export nodes.
 */
function rc_node_export_callback_export() {

    // Set up an array of nid_filters.
    $nid_filters = array();

    // The base nids.
    $args = array_filter(func_get_args(), 'is_numeric');
    if ($args) {
        $nid_filters['base'] = $args;
    }

    // Filter for values in the node table (except for nids).
    $filters = array(
        'status',
        'promote',
        'sticky',
        'translate',
        'language',
        'type',
    );
    
    $og = drush_get_option('og');
    $result = db_query("SELECT nid  FROM node LEFT JOIN og_membership og ON node.nid = og.etid WHERE og.gid = '$og'");
    foreach ($result as $row) {
        $nid_filters['filters'][] = $row->nid;
    }
    drush_print_r(count($nid_filters['filters']) .' nodes will be exported (dependencies included). ');
    if (empty($nid_filters))
        return;
    // Handle SQL option.
    $sql = drush_get_option('sql');
    if ($sql) {
        $result = db_query($sql);
        foreach ($result as $row) {
            $nid_filters['sql'][] = $row->nid;
        }
    }

    // Handle PHP option.
    $code = drush_get_option('code');
    if ($code) {
        ob_start();
        print eval("?><?php " . $code . " ?>");
        $result = ob_get_contents();
        ob_end_clean();
        if (is_array($result)) {
            $nid_filters['code'] = $result;
        } else {
            $nid_filters['code'] = explode(
                    ",", str_replace(array("\n", "\r", "\t", " "), '', $result)
            );
        }
    }

    if (count($nid_filters) > 1) {
        // Compute the intersect of all $nid_filters if there are more than one.
        $nids = call_user_func_array('array_intersect', $nid_filters);
    } elseif (count($nid_filters) == 1) {
        // Use the only filter if there is only one.
        $nids = reset($nid_filters);
    } else {
        // Is there are no filters at all, do a query to get all nids.
        $result = db_select('node', 'n')->fields('n', array('nid'))->execute();
        $nids = array();
        foreach ($result as $row) {
            $nids[] = $row->nid;
        }
    }

    // Handle format option.
    $format = drush_get_option('format');

    if (empty($nids)) {
        drush_set_error('DRUSH_NOT_COMPLETED', "No nodes found.");
    }

    $result = node_export($nids, $format, 'dt');

    if ($result['success']) {
        $filename = drush_get_option('file');

        if ($filename) {
            // Output data to file. Note this only takes a flat filename for the current directory.
            // If file exists, ask for whether to overwrite.
            if (file_exists($filename)) {
                if (!drush_confirm(dt("File $filename exists. Do you really want to overwrite?"))) {
                    return;
                }
            }
            // Write the file.
            file_put_contents($filename, $result['output']);
        } else {
            // stdout.
            drush_print_r($result['output']);
        }
    } else {
        // We have received an error message.
        drush_set_error('DRUSH_NOT_COMPLETED', strip_tags(implode("\n", $result['output'])));
    }
}