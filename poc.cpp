#pragma leco app

import casein;
import fff;
import silog;

static void log() {
  silog::log(silog::info, "timer");
}
static void quit() {
  casein::interrupt(casein::IRQ_QUIT);
}

struct init {
  fff::timer t1 { 100, log };
  fff::timer t2 { 1000, quit };
} i;

