// Band Limited ImPulse synth, resonating band pass filter
SynthDef(\Blipper, {arg freq=440, filter=1, res=1, pan=0, overtones=10, mul=1, vol=0.4, lagtime=0.02, att=0.1, dec=0.1; var out, env, freqSet;
	env=EnvGen.kr(Env.perc(att+Rand(0.0,0.07), dec, 1, -4), doneAction: 2);

	freqSet=2.collect({|index| freq+ ((((Rand(0,1))+0.2)*(((IRand(0,1))*2)-1))  )  } );
	freqSet.add(freq);
	out=Resonz.ar(Blip.ar(freqSet, overtones, mul).sum,freq*filter,res);
	Out.ar(0, Pan2.ar((out*env)*Lag.kr(vol, lagtime),pan));
}).add;

// Pbind(\note, Pseq([0,2,4], inf), \octave, 6, \instrument, \Blipper ).play;


// Percussive single sine
SynthDef(\PercSine, {arg freq=440, mul=1, vol=0.4, pan=0,att=0.02,dec=0.2,lag=0.02;var out, env;
	env=EnvGen.kr(Env.perc(att,dec), doneAction: 2);
	out=SinOsc.ar(freq, mul: mul)*env;
	Out.ar(0, Pan2.ar(out*Lag.kr(vol, lag), pan));
}).add;

// Pbind(\note, Pseq([0,2,4], inf), \octave, 6, \instrument, \PercSine ).play;


// Simple SineStack synth
SynthDef(\SineStackSynth, {arg freq=440, mul=0.3, vol=0.4, pan=0,att=0.02,dec=0.5,lag=0.02;var out, env, freqSet, mulSet;
	env=EnvGen.kr(Env.perc(att,dec), doneAction: 2);
	freqSet= 3.collect({|index| freq * index});
	mulSet= 3.collect({|index| ( ( 1 / 6 ) * ( 6 - index ) / 5 ) });
	out=( SinOsc.ar(freqSet, mulSet * mul ) * env ).sum;
	Out.ar(0, Pan2.ar(out*Lag.kr(vol, lag), pan));
}).add;

// Pbind(\note, Pseq([0,2,4], inf), \octave, 6, \instrument, \SineStackSynth ).play;



thisProcess.openUDPPort(7001); // attempt to open 7001

o = OSCresponderNode(nil, '/aninstrument', { arg t, r, msg; t.postln; r.postln; msg.postln; Synth( "\Blipper", [\freq, msg[1], \dec, msg[2], \mul, msg[3] ]);  }).add;

p = OSCresponderNode(nil, '/anotherinstrument', { arg t, r, msg; t.postln; r.postln; msg.postln; Synth( "\PercSine", [\freq,( msg[1] / 2.0 ), \mul, msg[3]]);  }).add;

p = OSCresponderNode(nil, '/andonemoreinstrument', { arg t, r, msg; t.postln; r.postln; msg.postln; Synth( "\SineStackSynth", [\freq,( msg[1] / 2.0 ), \mul, msg[3]]);  }).add;



TempoClock.default.tempo = 0.95


b = NetAddr.new("127.0.0.1", 7000);    // create the NetAddr|

~aVar = 0.0;
~aDur = 0.125;
Pbind(\amp, 0.0,
	\dur, ~aDur , \finish, Pfunc {|ev|
		~aVar = ~aVar + 1;
		if ( ~aVar == ( ( 1.0 / ~aDur ) + 1 ), { ~aVar = 1 });
		b.sendMsg("/timing", ~aVar, ~aDur ;

	)}
).play;


OSCFunc.trace(true); // Turn posting on
OSCFunc.trace(false); // Turn posting on
