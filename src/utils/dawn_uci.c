#include <uci.h>
#include <stdlib.h>
#include <datastorage.h>

#include "dawn_uci.h"

/*

dawn.metric.ht_support
dawn.metric.vht_support'
dawn.metric.rssi
dawn.metric.freq

 */

struct probe_metric_s uci_get_dawn_metric()
{
    struct probe_metric_s ret;

    struct uci_context *c;
    struct uci_ptr ptr;

    c = uci_alloc_context ();

    char tmp_ht_support[] = "dawn.metric.ht_support";
    if (uci_lookup_ptr (c, &ptr, tmp_ht_support, 1) != UCI_OK) {
        uci_perror(c, "uci_get_daw_metric Error");
        return ret;
    }
    if(ptr.o->type == UCI_TYPE_STRING)
        ret.ht_support = atoi(ptr.o->v.string);

    char tmp_vht_support[] = "dawn.metric.vht_support";
    if (uci_lookup_ptr (c, &ptr, tmp_vht_support, 1) != UCI_OK) {
        uci_perror(c, "uci_get_daw_metric Error");
        return ret;
    }
    if(ptr.o->type == UCI_TYPE_STRING)
        ret.vht_support = atoi(ptr.o->v.string);

    char tmp_no_ht_support[] = "dawn.metric.no_ht_support";
    if (uci_lookup_ptr (c, &ptr, tmp_no_ht_support, 1) != UCI_OK) {
        uci_perror(c, "uci_get_daw_metric Error");
        return ret;
    }
    if(ptr.o->type == UCI_TYPE_STRING)
        ret.no_ht_support = atoi(ptr.o->v.string);

    char tmp_no_vht_support[] = "dawn.metric.no_vht_support";
    if (uci_lookup_ptr (c, &ptr, tmp_no_vht_support, 1) != UCI_OK) {
        uci_perror(c, "uci_get_daw_metric Error");
        return ret;
    }
    if(ptr.o->type == UCI_TYPE_STRING)
        ret.no_vht_support = atoi(ptr.o->v.string);

    char tmp_rssi[] = "dawn.metric.rssi";
    if (uci_lookup_ptr (c, &ptr, tmp_rssi, 1) != UCI_OK) {
        uci_perror(c, "uci_get_daw_metric Error");
        return ret;
    }
    if(ptr.o->type == UCI_TYPE_STRING)
        ret.rssi = atoi(ptr.o->v.string);

    char tmp_freq[] = "dawn.metric.freq";
    if (uci_lookup_ptr (c, &ptr, tmp_freq, 1) != UCI_OK) {
        uci_perror(c, "uci_get_daw_metric Error");
        return ret;
    }
    if(ptr.o->type == UCI_TYPE_STRING)
        ret.freq = atoi(ptr.o->v.string);

    char tmp_util[] = "dawn.metric.chan_util";
    if (uci_lookup_ptr (c, &ptr, tmp_util, 1) != UCI_OK) {
        uci_perror(c, "uci_get_daw_metric Error");
        return ret;
    }
    if(ptr.o->type == UCI_TYPE_STRING)
        ret.chan_util = atoi(ptr.o->v.string);

    char tmp_min_rssi[] = "dawn.metric.min_rssi";
    if (uci_lookup_ptr (c, &ptr, tmp_min_rssi, 1) != UCI_OK) {
        uci_perror(c, "uci_get_daw_metric Error");
        return ret;
    }
    if(ptr.o->type == UCI_TYPE_STRING)
        ret.min_rssi = atoi(ptr.o->v.string);

    char tmp_max_chan_util[] = "dawn.metric.max_chan_util";
    if (uci_lookup_ptr (c, &ptr, tmp_max_chan_util, 1) != UCI_OK) {
        uci_perror(c, "uci_get_daw_metric Error");
        return ret;
    }
    if(ptr.o->type == UCI_TYPE_STRING)
        ret.max_chan_util = atoi(ptr.o->v.string);


    printf("Try to load min_probe_count\n");
    char tmp_min_probe_count[] = "dawn.metric.min_probe_count";
    if (uci_lookup_ptr (c, &ptr, tmp_min_probe_count, 1) != UCI_OK) {
        uci_perror(c, "uci_get_daw_metric Error");
        return ret;
    }
    if(ptr.o->type == UCI_TYPE_STRING)
        ret.min_probe_count = atoi(ptr.o->v.string);

    printf("Loaded metric: %d\n", ret.min_probe_count);

    uci_free_context(c);

    return ret;
}