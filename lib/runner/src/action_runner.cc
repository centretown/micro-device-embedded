// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT
#if defined(ARDUINO)
#include "action_runner.h"  // NOLINT

ActionRunner::ActionRunner(ActionParser* parser) : Runner(parser) {
  Parser* typeParser = this->parser()->parser();
  switch (this->parser()->type()) {
    case 'd': {
      DelayParser* d = reinterpret_cast<DelayParser*>(typeParser);
      runner_.d = new DelayRunner(d);
    } break;
    case 'm': {
      ModeParser* m = reinterpret_cast<ModeParser*>(typeParser);
      runner_.m = new ModeRunner(m);
    } break;
    case 'p': {
      PinParser* p = reinterpret_cast<PinParser*>(typeParser);
      runner_.p = new PinRunner(p);
    } break;

    default:
      break;
  }
}

void ActionRunner::Run() {
  if (parser()->ok()) {
    switch (parser()->type()) {
      case 'd':
        runner_.d->Run();
        break;
      case 'm':
        runner_.m->Run();
        break;
      case 'p':
        runner_.p->Run();
        break;

      default:
        break;
    }
  }
}
#endif  // ARDUINO
