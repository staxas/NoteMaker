/*
 * FileInterpreter.cpp
 *
 *  Created on: Jan 17, 2014
 *      Author: edwinrietmeijer
 */

#include "FileInterpreter.h"


void processFile( std::string filename, bool runAll ) {

	bool isStartOfComment = false;
	bool defaultStreamNameUsed= false;
	int lineNo = 0;
	std::vector<scriptcommand::ScriptCommand * > scriptLoop;
	customtypes::InterpMode currInterpMode;
	std::string lineToRead;
	std::string funcName = "";
	std::string newEntityName;
	int nrOfNewEntities;
	std::vector<double> centsToRels;

	std::vector<std::string>::const_iterator gsnPos;

	config::playScriptCommandStack.clear();


	std::ifstream fileToRead ( filename.c_str() );

	if ( fileToRead.is_open() )
	{
		while ( getline ( fileToRead, lineToRead ) )
		{
			lineNo++;

			// LINE TOKENIZE
			std::string::size_type start = 0;
			std::string::size_type pos = lineToRead.find(" ");
			std::string tok;
			std::vector<std::string> tokens;
			isStartOfComment = false;

//			Uncomment this line to dump script during processing
//			std::cout << lineNo << ": " << lineToRead << std::endl;

			while ( pos != std::string::npos )
			{
				tok = lineToRead.substr( start,  pos - start);
				if ( tok[ 0 ] == '#' ) {
					isStartOfComment = true;
				}
				start = pos + 1;
				pos = lineToRead.find( " ", start );
				if ( ! isStartOfComment && tok.size() > 0) {
					tokens.push_back( tok );
				}
			}
			tok = lineToRead.substr( start,  pos - start );
			if ( tok[ 0 ] == '#' ) {
				isStartOfComment = true;
			}

			if ( ! isStartOfComment && tok.size() > 0) {
				tokens.push_back( tok );
			}

			common::strVectorToLower( tokens );

			if ( ! tokens.empty() ) {
				funcName = tokens.at( 0 );
				tokens.erase( tokens.begin() );
			} else {
				funcName = "";
			}

			if ( funcName != "" && funcName[0] != '#' ) {

				ScriptCommandVars newScriptCommVars;
				newScriptCommVars.noteBlock = nullptr;
				newScriptCommVars.generator  = nullptr;
				newScriptCommVars.noteBlockFunction = customtypes::NO_NB_FUNC;
				newScriptCommVars.generatorFunction = customtypes::NO_GEN_FUNC;
				newScriptCommVars.streamName = &config::streamNames.front();
				newScriptCommVars.pitchSet = config::defaultPitch;
				newScriptCommVars.durationSet = config::defaultDuration;
				newScriptCommVars.velocitySet = config::defaultVelocity;
				newScriptCommVars.firstGenFuncInt = 0;

				// LINE INTERPRETER
				if ( funcName == "config" && runAll )
					currInterpMode = customtypes::CONFIG_MODE;
				if ( funcName == "init" && runAll )
					currInterpMode = customtypes::INIT_MODE;
				if ( funcName == "play" )
					currInterpMode = customtypes::PLAY_MODE;

				// CONFIG MODE
				if ( currInterpMode == customtypes::CONFIG_MODE ) {
					if( tokens.size() > 0 ) {
						if ( funcName == "centernote" ) {
							if ( common::isInt( tokens.front() ) ) {
								config::centerNote = common::stringToInt( tokens.front() );
							}
						}
						if ( funcName == "centerfreq" ) {
							if ( common::isDouble( tokens.front() ) ) {
								config::centerFreq = common::stringToDouble( tokens.front() );
							}
						}

						if ( funcName == "notecents" ) {
							std::vector<std::string>::iterator pos2;
							std::vector<double> noteRelsToAdd;
							for ( pos2 = tokens.begin(); pos2 != tokens.end(); ++pos2 ) {
								std::string thisStr =  *pos2;
								if ( common::isDouble( thisStr ) ) {
									noteRelsToAdd.push_back( musical::centToRel ( common::stringToDouble ( thisStr ) ) );
								}
							}
							if ( ! noteRelsToAdd.empty() ) {
								config::noteRelatives.clear();
								config::noteRelatives = noteRelsToAdd;
							} else {
								std::cout << "Line " << lineNo << " : no notecents in correct format ( double/int ) found" << std::endl;
							}
							// notecents to noteRels
						}


						if ( funcName == "pitch" ) {
							std::vector<std::string>::iterator pos2;
							std::vector<int> pitchesToAdd;
							for ( pos2 = tokens.begin(); pos2 != tokens.end(); ++pos2 ) {
								std::string thisStr =  *pos2;
								if ( common::isInt( thisStr ) ) {
									pitchesToAdd.push_back(  common::stringToInt ( thisStr ) );
								} else {
									std::cout << "Line " << lineNo << " : pitch " << thisStr << " not in correct format ( int )" << std::endl;
								}
							}
							if ( ! pitchesToAdd.empty() ) {
								config::pitchStack.push_back( pitchesToAdd );
							} else {
								std::cout << "Line " << lineNo << " : no pitches in correct format ( int ) found" << std::endl;
							}
							// pitches to pitchStack
						}

						if ( funcName == "dur" ) {
							std::vector<std::string>::iterator pos2;
							std::vector<double> durationsToAdd;
							for ( pos2 = tokens.begin(); pos2 != tokens.end(); ++pos2 ) {
								std::string thisStr =  *pos2;
								if ( common::isDouble( thisStr ) ) {
									durationsToAdd.push_back( common::stringToDouble ( thisStr ) );
								} else {
									std::cout << "Line " << lineNo << " : duration " << thisStr << " not in correct format ( double )" << std::endl;
								}
							}
							if ( !durationsToAdd.empty() ) {
								config::durationStack.push_back( durationsToAdd );
							} else {
								std::cout << "Line " << lineNo << " : no durations in correct format ( double ) found" << std::endl;
							}
							// durations to durationStack
						}

						if ( funcName == "vel" ) {
							std::vector<std::string>::iterator pos2;
							std::vector<double> velocitiesToAdd;
							for ( pos2 = tokens.begin(); pos2 != tokens.end(); ++pos2 ) {
								std::string thisStr =  *pos2;
								if ( common::isDouble( thisStr ) ) {
									velocitiesToAdd.push_back(  common::stringToDouble ( thisStr ) );
								} else {
									std::cout << "Line " << lineNo << " : velocity " << thisStr << " not in correct format ( double )" << std::endl;
								}
							}
							if ( ! velocitiesToAdd.empty() ) {
								config::velocityStack.push_back( velocitiesToAdd );
							} else {
								std::cout << "Line " << lineNo << " : no velocities in correct format ( double ) found" << std::endl;
							}
							// velocities to velocityStack
						}

						if ( funcName == "defaultpitch" ) {
							if ( config::pitchStack.size() > 0 && common::isInt( tokens.front() ) ) {
								if (  common::stringToInt( tokens.front() ) <= config::pitchStack.size() ) {
									config::defaultPitch = & config::pitchStack.at( common::stringToInt( tokens.front() ) -1 );
								} else {
									std::cout << "Line " << lineNo << " : default pitch index " << common::stringToInt( tokens.front() ) << " not found, returning internal default" << std::endl;
								}
							} else {
								std::cout << "Line " << lineNo << " : default pitch index value " << tokens.front() << " can not be processed" << std::endl;
							}
						}

						if ( funcName == "defaultdur" ) {
							if ( config::durationStack.size() > 0 && common::isInt( tokens.front() ) ) {
								if (  common::stringToInt( tokens.front() ) <= config::durationStack.size() ) {
									config::defaultDuration = & config::durationStack.at( common::stringToInt( tokens.front() ) -1 );
								} else {
									std::cout << "Line " << lineNo << " : default duration index " << common::stringToInt( tokens.front() ) << " not found, returning internal default" << std::endl;
								}
							} else {
								std::cout << "Line " << lineNo << " : default duration index value " << tokens.front() << " can not be processed" << std::endl;
							}
						}

						if ( funcName == "defaultvel" ) {
							if ( config::velocityStack.size() > 0 && common::isInt( tokens.front() ) ) {
								if (  common::stringToInt( tokens.front() ) <= config::velocityStack.size() ) {
									config::defaultVelocity = & config::velocityStack.at( common::stringToInt( tokens.front() ) -1 );
								} else {
									std::cout << "Line " << lineNo << " : default velocity index " << common::stringToInt( tokens.front() ) << " not found, returning internal default" << std::endl;
								}
							} else {
								std::cout << "Line " << lineNo << " : default velocity index value " << tokens.front() << " can not be processed" << std::endl;
							}
						}

						// ADD NEW ENTITIES
						if ( funcName == "new" ) {
							bool entityFound = false;
							if ( tokens.size() > 0 ) {
								newEntityName = tokens.at( 0 );
								tokens.erase( tokens.begin() );
								nrOfNewEntities = 1;
								// Number of new entities to add given?
								if ( tokens.size() > 0 && common::isInt( tokens.front() ) ) {
									nrOfNewEntities = common::stringToInt( tokens.front() );
								}

								// Check script name file for existing generators, add to the generator stack when found
								for ( int i = 0; i < nrOfNewEntities; i++ ) {

									// Cycle through accepted generator script names as supported in GenAdmin.h/.cpp
									for ( gsnPos = generatorScriptNames.begin(); gsnPos != generatorScriptNames.end(); ++gsnPos ) {
										if ( newEntityName == common::lower( *gsnPos ) ) {

											// Add the generator to the generator stack and generator ID stack
											addGen( findGenScriptName( newEntityName ), config::generatorStack, config::generatorIds );

											// Initialize generator
											config::generatorStack.back() -> setMediatorPointers( config::genMediatorVars, config::mutatorMediatorVars  );
											config::generatorStack.back() -> setScaleSize( config::noteRelatives.size() );
								     		config::generatorStack.back() -> setDia( config::isDiatonic );
											config::generatorStack.back() -> init();


											entityFound = true;
										}
									}

									if ( newEntityName == "stream" ) {
										//								config::streamStack.push_back( new noteblock::NoteBlock );
										if ( tokens.front() != "" ) {
											config::streamNames.push_back( tokens.front() );
											entityFound = true;
										} else {
											if ( ! defaultStreamNameUsed ) {
												//												config::streamNames.push_back( "default" );
												std::cout << "Line " << lineNo << " : stream name in use, using \'default\'" << std::endl;
												entityFound = true;
											}
										}
									}
									if ( newEntityName == "noteblock" ) {
										config::noteBlockStack.push_back( new noteblock::NoteBlock );
										entityFound = true;
									}
								}
							}
							if ( ! entityFound ) {
								std::cout << "Line " << lineNo << " : entity type not found" << std::endl;
							}
						}
					}
				}

				// INIT MODE
				if ( currInterpMode == customtypes::INIT_MODE ) {

					// From here, the vector of tokens can be sent to a subfunction to be processed
					// into a ScriptCommand var set.


					bool isCompleteScriptCommand;
					isCompleteScriptCommand = tokensToScriptVars( funcName, tokens, newScriptCommVars, lineNo );

					if ( isCompleteScriptCommand ) {
						config::initScriptCommandStack.push_back( new scriptcommand::ScriptCommand ( newScriptCommVars ) );
						config::initScriptCommandStack.back() -> setMediatorPointers( config::genMediatorVars, config::mutatorMediatorVars );
						config::initScriptCommandStack.back() -> setConfigPointers( config::centerNote, config::centerFreq, config::noteRelatives );
					}
				}
				//				gotFirstLoopOpenBracket

				// PLAY MODE
				if ( currInterpMode == customtypes::PLAY_MODE ) {

					tokensToScriptVars( funcName, tokens, newScriptCommVars, lineNo );

					if ( newScriptCommVars.noteBlock != nullptr  && newScriptCommVars.noteBlockFunction != customtypes::NO_NB_FUNC ) {
						scriptLoop.push_back( new scriptcommand::ScriptCommand ( newScriptCommVars ) );
						scriptLoop.back() -> setMediatorPointers( config::genMediatorVars, config::mutatorMediatorVars );
						scriptLoop.back() -> setConfigPointers( config::centerNote, config::centerFreq, config::noteRelatives );
					}

					if ( funcName =="}" && !scriptLoop.empty() ) {
						config::playScriptCommandStack.push_back( scriptLoop );

						config::loopWaitFor.push_back( 0.0 );
						config::loopTimePassed.push_back( 0.0 );
						config::loopCurrentIndex.push_back( 0 );
						scriptLoop.clear();
					}
				}
			} // end of emtpy function check
			// next line or eof
		}

		if ( ! scriptLoop.empty() ) {
			config::playScriptCommandStack.push_back( scriptLoop );
			config::loopWaitFor.push_back( 0.0 );
			config::loopTimePassed.push_back( 0.0 );
			scriptLoop.clear();
		}

		//		std::cout << scriptcommand::initScriptCommandStack.size() << std::endl;
		//
		//		std::cout << (scriptcommand::playScriptCommandStack.front()).size() << std::endl;
		//		std::cout << (scriptcommand::playScriptCommandStack.back()).size() << std::endl;

		fileToRead.close();
	}
	else std::cout << "Unable to open read file";
}

bool tokensToScriptVars( std::string & funcName, std::vector<std::string> & tokens, ScriptCommandVars & newScriptCommVars, int & lineNo ) {

	bool completeScriptCommand = false;

	if ( funcName != "noteblock" ) {
		newScriptCommVars.noteBlock = nullptr;

		bool isGen = false;
		generator::Generator * aNewGen = findGenScriptName( funcName );
		if( aNewGen -> getScriptName() != "" ) {
			isGen = true;
			// end of genType existance check

			if ( ! isGen ) {
				std::cout << "Line " << lineNo << " : generator type for generator script name '" << funcName << "' does not exist" << std::endl;
			}

			if( isGen && tokens.size() > 0 ) {
				// Check if the given generator index of this type exists in the stack
				// Note: a generator of index 2 could have a higher placement index
				// in the generatorStack vector, depending on how many other generators
				// of (a) different type(s) are in the stack
				int genNr;
				bool isGenInStack = false;
				int genStackIndex = -1;
				if ( common::isInt( tokens.at( 0 ) ) ) {
					genNr = common::stringToInt( tokens.at( 0 ) );
					tokens.erase( tokens.begin() );
					genStackIndex = getGenStackIndex( aNewGen, genNr );
					// If a generator of the type and and index specified exists on the
					// generator stack, point to it in the new ScriptCommandVars struct.
					if ( genStackIndex != -1 ) {
						newScriptCommVars.generator = config::generatorStack.at( genStackIndex );
						isGenInStack = true;
					}
				} // end of generator index check

				if ( ! isGenInStack ) {
					std::cout << "Line " << lineNo << " : generator stack index " << genNr << " for generator script name '" << funcName<< "' does not exist" << std::endl;
				}

				if ( isGenInStack && tokens.size() > 0 ) {
					// Find and, if it exists, add non-noteBlock generator function to script
					bool isGenFunc = false;
					std::string genFuncCall = tokens.at( 0 );
					tokens.erase( tokens.begin() );

					for ( int i = 0; i < customtypes::nonNoteBlockGeneratorFuncs.size(); i++ ) {

						if( genFuncCall == customtypes::nonNoteBlockGeneratorFuncsScriptNames.at( i ) ) {

							isGenFunc = true;
							completeScriptCommand = true;
							newScriptCommVars.generatorFunction = customtypes::nonNoteBlockGeneratorFuncs.at( i );
						}
					} // end of generator function existance check
				}
			}
			std::vector<std::string>::iterator pos2;
			std::vector<double> variablesToAdd;

			for ( pos2 = tokens.begin(); pos2 != tokens.end(); ++pos2 ) {
				std::string thisStr =  *pos2;
				if ( common::isDouble( thisStr ) ) {
					variablesToAdd.push_back(  common::stringToDouble ( thisStr ) );
				} else {
					std::cout << "Line " << lineNo << " : variable '" << thisStr << "' not in correct format ( double )" << std::endl;
				}
			}

			if ( ! variablesToAdd.empty() ) {
				newScriptCommVars.variableSet = variablesToAdd;
				completeScriptCommand = true;
			}
			//			else {
			//				std::cout << "Line " << lineNo << " : no variables in correct format ( double ) found" << std::endl;
			//			}
			// variables to script command struct
		}

	} else {

		// Found noteblock based line of script
		if( tokens.size() > 0 ) {
			if( common::isInt( tokens.at( 0 ) ) ) {
				// Get noteBlockStack index number
				int noteBlockNo = common::stringToInt( tokens.at( 0 ) );
				tokens.erase( tokens.begin() );

				// Check to see if given noteBlockStack index number exists
				if( noteBlockNo < config::noteBlockStack.size() && noteBlockNo > -1 ) {

					// Set noteBlock index in new ScriptCommandVars
					newScriptCommVars.noteBlock = config::noteBlockStack.at( noteBlockNo );
				}

				if ( tokens.size() > 0 ) {
					// Find and, if it exists, add noteBlock Function to script

					bool isNBFunc = false;
					std::string nbFuncCall = tokens.at( 0 );
					tokens.erase( tokens.begin() );
					for ( int i = 0; i < customtypes::noteBlockFuncScriptNames.size(); i++ ) {
						if( nbFuncCall == customtypes::noteBlockFuncScriptNames.at( i ) ) {
							isNBFunc = true;
							newScriptCommVars.noteBlockFunction = customtypes::allNoteBlockFuncs.at( i );
						}
					}

					if ( ! isNBFunc ) {
						std::cout << "Line " << lineNo << " : script noteblock function reference '" << nbFuncCall << "' does not exist" << std::endl;
					}

					//Add default pitch, duration, and velocity vector pointers now.
					newScriptCommVars.pitchSet = config::defaultPitch;
					newScriptCommVars.durationSet = config::defaultDuration;
					newScriptCommVars.velocitySet = config::defaultVelocity;

					if ( isNBFunc && tokens.size() > 0 ) {
						// Check for existing of generator type
						bool isGen = false;
						std::string genScrName = tokens.at( 0 );
						tokens.erase( tokens.begin() );
						bool isGenNonNBFunc = false;

						// Check to see if noteblock function is a non-generator noteblock function
						std::vector<customtypes::NoteBlockFunc>::const_iterator ngfPos;
						for( ngfPos = customtypes::nonGeneratorNoteBlockFuncs.begin(); ngfPos != customtypes::nonGeneratorNoteBlockFuncs.end(); ++ngfPos ) {
							if( newScriptCommVars.noteBlockFunction == *ngfPos ) {
								isGenNonNBFunc = true;
								completeScriptCommand = true;
							}
						}

						// If noteblock function is NOT a non-generator noteblock function,
						// try to find a generator stack reference in script line
						if( ! isGenNonNBFunc ) {
							generator::Generator * aNewGen = findGenScriptName( genScrName );
							if( aNewGen -> getScriptName() != "" ) {
								isGen = true;
							} // end of genType existance check

							if ( ! isGen ) {
								std::cout << "Line " << lineNo << " : generator type for generator script name '" << genScrName << "' does not exist" << std::endl;
							}
							if( isGen && tokens.size() > 0 ) {
								// Check if the given generator index of this type exists in the stack
								// Note: a generator of index 2 could have a higher placement index
								// in the generatorStack vector, depending on how many other generators
								// of (a) different type(s) are in the stack
								int genNr;
								bool isGenInStack = false;
								int genStackIndex = -1;
								if ( common::isInt( tokens.at( 0 ) ) ) {
									genNr = common::stringToInt( tokens.at( 0 ) );
									tokens.erase( tokens.begin() );
									genStackIndex = getGenStackIndex( aNewGen, genNr );
									// If a generator of the type and and index specified exists on the
									// generator stack, point to it in the new ScriptCommandVars struct.
									if ( genStackIndex != -1 ) {
										newScriptCommVars.generator = config::generatorStack.at( genStackIndex );
										isGenInStack = true;
									}
								} // end of generator index check

								if ( ! isGenInStack ) {
									std::cout << "Line " << lineNo << " : generator stack index " << genNr << " for generator script name '" << genScrName<< "' does not exist" << std::endl;
								}

								if ( isGenInStack && tokens.size() > 0 ) {
									// Find and, if it exists, add generator Function to script
									bool isGenFunc = false;
									std::string genFuncCall = tokens.at( 0 );
									tokens.erase( tokens.begin() );
									for ( int i = 0; i < customtypes::generatorFuncScriptNames.size(); i++ ) {
										if( genFuncCall == customtypes::generatorFuncScriptNames.at( i ) ) {
											isGenFunc = true;
											completeScriptCommand = true;
											newScriptCommVars.generatorFunction = customtypes::allGeneratorFuncs.at( i );
										}
									} // end of generator function existance check

									// Check to see if the generator function is a mutator function.
									// If so, the next variable must be a noteblock
									bool isGenFuncMutatorFunc = false;
									for ( int i = 0; i < customtypes::mutatorGeneratorFuncs.size(); i++ ) {
										if ( newScriptCommVars.generatorFunction == customtypes::mutatorGeneratorFuncs.at( i ) ) {
											isGenFuncMutatorFunc = true;
										}
									}

									std::string nextToken;
									if( isGenFuncMutatorFunc ) {
										completeScriptCommand = false;

										if ( tokens.size() > 0 ) {
											nextToken = tokens.at( 0 );
											tokens.erase( tokens.begin() );
										}
									}

									if ( nextToken == "noteblock" ) {
										if ( tokens.size() > 0 ) {
											std::string noteBlockNo = tokens.at( 0 );
											tokens.erase( tokens.begin() );
											if( common::isInt( noteBlockNo ) ) {

												int noteBlockIndex = common::stringToInt( noteBlockNo );
												if( noteBlockIndex < config::noteBlockStack.size() && noteBlockIndex > -1 ) {
													// Set noteBlock index in new ScriptCommandVars
													newScriptCommVars.anotherNoteBlock = config::noteBlockStack.at( noteBlockIndex );
													completeScriptCommand = true;

												}
											}
										}
									}

									// Check to see if the next variable is an int. This will be the value passed with the generator function
									// MIGHT NOT BE INT!
									if ( isGenInStack && tokens.size() > 0 ) {
										bool isVarInt= false;
										if( common::isInt( tokens.at( 0 ) ) ) {
											// Get int value
											newScriptCommVars.firstGenFuncInt = common::stringToInt( tokens.at( 0 ) );
											tokens.erase( tokens.begin() );
											isVarInt = true;
										}
										// If there is an int variable, increment the generator function:
										// GET becomes GET_INT, NEXT becomes NEXT_INT, etcetera
										if( isVarInt ) {
											int genFuncNo = static_cast<int>( newScriptCommVars.generatorFunction );
											++ genFuncNo;
											newScriptCommVars.generatorFunction = static_cast<customtypes::GeneratorFunc>( genFuncNo );
										}
									}
								}

								// Process remaining tokens
								while( ! tokens.empty() ) {
									std::string nextString = tokens.at( 0 );
									tokens.erase( tokens.begin() );

									if ( nextString == "pitch" ) {
										if( tokens.size() > 0 ) {
											if( common::isInt( tokens.at( 0 ) ) ) {
												int pitchIndex = common::stringToInt( tokens.at( 0 ) ) - 1;
												tokens.erase( tokens.begin() );
												if ( pitchIndex < config::pitchStack.size() && pitchIndex > -1 ) {
													newScriptCommVars.pitchSet = & config::pitchStack.at( pitchIndex );
												}
											}
										}
									} // end of check for pitch index ref

									if ( nextString == "dur" || nextString == "duration" ) {
										if( tokens.size() > 0 ) {
											if( common::isInt( tokens.at( 0 ) ) ) {
												int durIndex = common::stringToInt( tokens.at( 0 ) ) - 1;
												tokens.erase( tokens.begin() );
												if ( durIndex < config::durationStack.size() && durIndex > -1 ) {
													newScriptCommVars.durationSet = & config::durationStack.at( durIndex );
												}
											}
										}
									} // end of check for duration index ref

									if ( nextString == "vel" || nextString == "velocity" ) {
										if( tokens.size() > 0 ) {
											if( common::isInt( tokens.at( 0 ) ) ) {
												int velIndex = common::stringToInt( tokens.at( 0 ) ) - 1;
												tokens.erase( tokens.begin() );
												if ( velIndex < config::velocityStack.size() && velIndex > -1 ) {
													newScriptCommVars.velocitySet = & config::velocityStack.at( velIndex );
												}
											}
										}
									} // end of check for duration index ref

								} // end of remaining tokens processing

							} // end of noteblock script line processing
						}

						if( newScriptCommVars.noteBlockFunction == customtypes::PLAY ) {
							newScriptCommVars.generatorFunction = customtypes::NO_GEN_FUNC;
							std::string thisStreamName = "default";
							while( ! tokens.empty() ) {
								std::string nextToken = tokens.at( 0 );
								tokens.erase( tokens.begin() );
								std::vector<std::string>::iterator strPos;
								for( strPos = config::streamNames.begin(); strPos != config::streamNames.end(); ++strPos ) {
									if ( nextToken == * strPos ) {
										newScriptCommVars.streamName = &( *strPos );
									}
								}
							}
						}
					}
				}
			}
		}
	} // end of noteblock script function
	return completeScriptCommand;
}


void writeToFile( std::string filename, const std::string & lineToWrite ) {
	std::ofstream fileToWrite( filename.c_str(), std::ios::app );
	if (fileToWrite.is_open())
	{
		fileToWrite << lineToWrite;
		fileToWrite.close();
	}
	else std::cout << "Unable to open write file";
}

void fileToScreen( std::string filename ) {
	std::string lineToRead;
	std::ifstream fileToRead ( filename.c_str() );
	if (fileToRead.is_open())
	{
		while ( getline (fileToRead,lineToRead) )
		{
			std::cout << lineToRead << std::endl;
		}
		fileToRead.close();
	}
	else std::cout << "Unable to open read file";
}

