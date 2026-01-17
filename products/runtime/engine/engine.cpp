#include "engine.hxx"
#include "../utility/debug.hxx"
#include "opcode.hxx"
#include <cstdint>
#include <bit>
#include "state.hxx"

void dump(Fibre* f) {
    LOG("=== Fibre @ ===\n");

    LOG("R1:\n");
    LOG("  u64 = %llu\n", (unsigned long long)f->registers[RegisterID::R1].u64);
    LOG("  u32 = %u\n",  f->registers[RegisterID::R1].u32);
    LOG("  u16 = %u\n",  f->registers[RegisterID::R1].u16);
    LOG("  u8  = %u\n",  f->registers[RegisterID::R1].u8);
    LOG("  i64 = %lld\n", (long long)f->registers[RegisterID::R1].i64);
    LOG("  i32 = %d\n",  f->registers[RegisterID::R1].i32);
    LOG("  i16 = %d\n",  f->registers[RegisterID::R1].i16);
    LOG("  i8  = %d\n",  f->registers[RegisterID::R1].i8);
    LOG("  f32 = %f\n",  f->registers[RegisterID::R1].f32);
    LOG("  f64 = %lf\n", f->registers[RegisterID::R1].f64);

    LOG("R2:\n");
    LOG("  u64 = %llu\n", (unsigned long long)f->registers[RegisterID::R2].u64);
    LOG("  u32 = %u\n",  f->registers[RegisterID::R2].u32);
    LOG("  u16 = %u\n",  f->registers[RegisterID::R2].u16);
    LOG("  u8  = %u\n",  f->registers[RegisterID::R2].u8);
    LOG("  i64 = %lld\n", (long long)f->registers[RegisterID::R2].i64);
    LOG("  i32 = %d\n",  f->registers[RegisterID::R2].i32);
    LOG("  i16 = %d\n",  f->registers[RegisterID::R2].i16);
    LOG("  i8  = %d\n",  f->registers[RegisterID::R2].i8);
    LOG("  f32 = %f\n",  f->registers[RegisterID::R2].f32);
    LOG("  f64 = %lf\n", f->registers[RegisterID::R2].f64);

    LOG("ROUT:\n");
    LOG("  u64 = %llu\n", (unsigned long long)f->registers[RegisterID::ROUT].u64);
    LOG("  u32 = %u\n",  f->registers[RegisterID::ROUT].u32);
    LOG("  u16 = %u\n",  f->registers[RegisterID::ROUT].u16);
    LOG("  u8  = %u\n",  f->registers[RegisterID::ROUT].u8);
    LOG("  i64 = %lld\n", (long long)f->registers[RegisterID::ROUT].i64);
    LOG("  i32 = %d\n",  f->registers[RegisterID::ROUT].i32);
    LOG("  i16 = %d\n",  f->registers[RegisterID::ROUT].i16);
    LOG("  i8  = %d\n",  f->registers[RegisterID::ROUT].i8);
    LOG("  f32 = %f\n",  f->registers[RegisterID::ROUT].f32);
    LOG("  f64 = %lf\n", f->registers[RegisterID::ROUT].f64);
    LOG("FLAG: %u\n", f->flag);

    LOG("RPC = %llu\n", (unsigned long long)f->RPC);
}


void fetch(uint64_t left, uint64_t right, uint16_t& opcode, uint16_t& val1, uint32_t& val2, uint64_t& val3) {
	
	opcode = left >> 48; //upper 16 bits
	val1 = left >> 32; //first value
	val2 = left; //auto truncates.
	val3 = right; //literally this.
	
}

void *run(void *args) {

	RunnerState *state = static_cast<RunnerState *>(args);
	//runs the opcodes here
	uint16_t opcode;
	uint16_t val1;
	uint32_t val2;
	uint64_t val3;
	Fibre *fibre = state->worker->fibres->node;
	CDLLWrapper<Fibre> *current = state->worker->fibres;
	
	while(true) {

		fetch(
			state->factory->instructions[ fibre->RPC ], 
			state->factory->instructions[ fibre->RPC + 1 ], 
			opcode, val1, val2, val3
		);
		
		fibre->RPC += 2;
		
		if ( fibre->status == FibreStatus::WAITING ) {
			fibre = current->next->node;
			current = current->next;
			continue; //for re-fetch basically.
		}
		
		switch (opcode) {
			//classic register arithmetic here
			case OPCODES::iadd: {
				LOG("iadd is being called\n");
				fibre->registers[RegisterID::ROUT].i64 = fibre->registers[RegisterID::R1].i64 + fibre->registers[RegisterID::R2].i64;
				break;
			}
			case OPCODES::isub: {
				fibre->registers[RegisterID::ROUT].i64 = fibre->registers[RegisterID::R1].i64 - fibre->registers[RegisterID::R2].i64;
				break;
			}
			case OPCODES::imul: {
				fibre->registers[RegisterID::ROUT].i64 = fibre->registers[RegisterID::R1].i64 * fibre->registers[RegisterID::R2].i64;
				break;
			}
			case OPCODES::idiv: {
				if ( fibre->registers[RegisterID::R2].i64 != 0 ) {
					fibre->registers[RegisterID::ROUT].i64 = fibre->registers[RegisterID::R1].i64 / fibre->registers[RegisterID::R2].i64;
				} else {
					LOG("Division by Zero Error");
				}
				break;
			}
			///////////////////////////////////
			case OPCODES::uadd: {
				fibre->registers[RegisterID::ROUT].u64 = fibre->registers[RegisterID::R1].u64 + fibre->registers[RegisterID::R2].u64;
				break;
			}
			case OPCODES::usub: {
				fibre->registers[RegisterID::ROUT].u64 = fibre->registers[RegisterID::R1].u64 - fibre->registers[RegisterID::R2].u64;
				break;
			}
			case OPCODES::umul: {
				fibre->registers[RegisterID::ROUT].u64 = fibre->registers[RegisterID::R1].u64 * fibre->registers[RegisterID::R2].u64;
				break;
			}
			case OPCODES::udiv: {
				if ( fibre->registers[RegisterID::R2].u64 != 0 ) {
					fibre->registers[RegisterID::ROUT].u64 = fibre->registers[RegisterID::R1].u64 / fibre->registers[RegisterID::R2].u64;
				} else {
					LOG("Division by Zero Error");
				}
				break;
			}
			/////////////////////////////////
			case OPCODES::fadd: {
				fibre->registers[RegisterID::ROUT].f32 = fibre->registers[RegisterID::R1].f32 + fibre->registers[RegisterID::R2].f32;
				break;
			}
			case OPCODES::fsub: {
				fibre->registers[RegisterID::ROUT].f32 = fibre->registers[RegisterID::R1].f32 - fibre->registers[RegisterID::R2].f32;
				break;
			}
			case OPCODES::fmul: {
				fibre->registers[RegisterID::ROUT].f32 = fibre->registers[RegisterID::R1].f32 * fibre->registers[RegisterID::R2].f32;
				break;
			}
			case OPCODES::fdiv: {
				fibre->registers[RegisterID::ROUT].f32 = fibre->registers[RegisterID::R1].f32 / fibre->registers[RegisterID::R2].f32;
				break;
			}
			//////////////////////////////////
			case OPCODES::dadd: {
				fibre->registers[RegisterID::ROUT].f64 = fibre->registers[RegisterID::R1].f64 + fibre->registers[RegisterID::R2].f64;
				break;
			}
			case OPCODES::dsub: {
				fibre->registers[RegisterID::ROUT].f64 = fibre->registers[RegisterID::R1].f64 - fibre->registers[RegisterID::R2].f64;
				break;
			}
			case OPCODES::dmul: {
				fibre->registers[RegisterID::ROUT].f64 = fibre->registers[RegisterID::R1].u64 * fibre->registers[RegisterID::R2].f64;
				break;
			}
			case OPCODES::ddiv: {
				fibre->registers[RegisterID::ROUT].f64 = fibre->registers[RegisterID::R1].f64 / fibre->registers[RegisterID::R2].f64;
				break;
			}
			//inline arithmetic here
			case OPCODES::ixadd: {
				fibre->registers[ val1 ].i64 += (int64_t)val3;
				break;
			}
			case OPCODES::ixsub: {
				fibre->registers[ val1 ].i64 -= (int64_t)val3;
				break;
			}
			case OPCODES::ixmul: {
				fibre->registers[ val1 ].i64 *= (int64_t)val3;
				break;
			}
			case OPCODES::ixdiv: {
				fibre->registers[ val1 ].i64 /= (int64_t)val3;
				break;
			}
			
			
			case OPCODES::uxadd: {
				fibre->registers[ val1 ].u64 += val3;
				break;
			}
			case OPCODES::uxsub: {
				fibre->registers[ val1 ].u64 -= val3;
				break;
			}
			case OPCODES::uxmul: {
				fibre->registers[ val1 ].u64 *= val3;
				break;
			}	
			case OPCODES::uxdiv: {
				fibre->registers[ val1 ].u64 /= val3;
				break;
			}
			
			case OPCODES::fxadd: {
				LOG("fxadd being called\n");
				LOG("Value 1: %d\nValue 3: %lu", val1, val3);
				fibre->registers[ val1 ].f32 += std::bit_cast<float>((uint32_t)val3);
				break;
			}
			case OPCODES::fxsub: {
				LOG("fxadd being called\n");
				LOG("Value 1: %d\nValue 3: %lu", val1, val3);
				fibre->registers[ val1 ].f32 -= std::bit_cast<float>((uint32_t)val3);
				break;
			}
			case OPCODES::fxmul: {
				LOG("fxadd being called\n");
				LOG("Value 1: %d\nValue 3: %lu", val1, val3);
				fibre->registers[ val1 ].f32 *= std::bit_cast<float>((uint32_t)val3);
				break;
			}
			case OPCODES::fxdiv: {
				LOG("fxadd being called\n");
				LOG("Value 1: %d\nValue 3: %lu", val1, val3);
				fibre->registers[ val1 ].f32 /= std::bit_cast<float>((uint32_t)val3);
				break;
			}
			
			case OPCODES::dxadd: {
				LOG("fxadd being called\n");
				LOG("Value 1: %d\nValue 3: %lu", val1, val3);
				fibre->registers[ val1 ].f64 += std::bit_cast<double>(val3);
				break;
			}
			case OPCODES::dxsub: {
				LOG("fxadd being called\n");
				LOG("Value 1: %d\nValue 3: %lu", val1, val3);
				fibre->registers[ val1 ].f64 -= std::bit_cast<double>(val3);
				break;
			}
			case OPCODES::dxmul: {
				LOG("fxadd being called\n");
				LOG("Value 1: %d\nValue 3: %lu", val1, val3);
				fibre->registers[ val1 ].f64 *= std::bit_cast<double>(val3);
				break;
			}
			case OPCODES::dxdiv: {
				LOG("fxadd being called\n");
				LOG("Value 1: %d\nValue 3: %lu", val1, val3);
				fibre->registers[ val1 ].f64 /= std::bit_cast<double>(val3);
				break;
			}
			
			case OPCODES::rbcrop: {
				fibre->registers[ RegisterID::ROUT ].u64 = val1 >> (fibre->registers[RegisterID::R1].u64 << val1);
				break;
			}
			case OPCODES::lbcrop: {
				fibre->registers[ RegisterID::ROUT ].u64 = (fibre->registers[RegisterID::R1].u64 >> val1) << val1;
				break;
			}
			case OPCODES::drbcrop: {
				fibre->registers[ RegisterID::ROUT ].u64 = 
					fibre->registers[RegisterID::R2].u8 >> (fibre->registers[RegisterID::R1].u64 << fibre->registers[RegisterID::R2].u8);
				break;
			}
			case OPCODES::dlbcrop: {
				fibre->registers[ RegisterID::ROUT ].u64 = 
					(fibre->registers[RegisterID::R1].u64 >> fibre->registers[RegisterID::R2].u8) << fibre->registers[RegisterID::R2].u8;
				break;
			}
			
			case OPCODES::icf: {
				fibre->registers[RegisterID::ROUT].u64 = 
					static_cast<uint64_t>(
						std::bit_cast<uint32_t>(
							static_cast<float>(
								static_cast<int32_t>(
									std::bit_cast<int64_t>( fibre->registers[RegisterID::R1].u64 )
								)
							)
						)
					);
				break;
			}
			
			case OPCODES::fci: {
				//the data is in uint64_t.
				// uint64_t -> uint32_t -> int32_t -> float
				//
				fibre->registers[RegisterID::ROUT].u64 = 
					std::bit_cast<uint64_t>(
						static_cast<int64_t>(
							static_cast<int32_t>(
								std::bit_cast<float>(
									static_cast<uint32_t>( fibre->registers[RegisterID::R1].u64 )
								)
							)
						)
					);
				break;
			}
			
			case OPCODES::lcd: {
				
				//long to double is simple, it's just bitcasting!
				
				fibre->registers[RegisterID::ROUT].u64=
					std::bit_cast<uint64_t>(
						static_cast<double>(
							std::bit_cast<int64_t>(
								fibre->registers[RegisterID::R1].u64
							)
						)
					);
				
				break;
				
			}
			
			case OPCODES::dcl: {
				
				fibre->registers[RegisterID::ROUT].u64=
					std::bit_cast<uint64_t>(
						static_cast<int64_t>(
							std::bit_cast<double>(
								fibre->registers[RegisterID::R1].u64
							)
						)
					);
				
				break;
				
			}
			
			case OPCODES::jif: {
				if ( fibre->flag == 1 ) {
					fibre->RPC =  val3;
					fibre->flag = 0;
				}
				break;
			}
			
			case OPCODES::jifn: {
				if ( fibre->flag == 0 ) {
					fibre->RPC =  val3;
					fibre->flag = 0;
				}
				break;
			}
			
			case OPCODES::jmp: {
				fibre->RPC = val3;
				break;
			}
			
			case OPCODES::scall: {
				if ( val3+1 > state->factory->tray->length ) {
					LOG("DEBUG::ERROR -> INVALID SYSCALL INDEX\n");
				} else {
					state->factory->tray->functions[val3](fibre);
				}
				break;
			}
			
			case OPCODES::yield: {
				//okay, yield switches the fibre itself, nothing else.
				fibre = current->next->node;
				current = current->next;
				break;
			}
			
			case OPCODES::launch: {
				//TODO
				//The launch opcode is obvious - it launches a new fibre (not worker) in the current fibre pool with
				//the PC register being set to whatever the 8 byte value is.
				Fibre *fib = Fibre::init();
				fib->RPC = val3; //because this is the actual address.
				
				Worker::addFibre(state->worker, fib);
				
				break;
			}
			
			case OPCODES::launch_worker: {
				//this is basically creating a new worker and an active fibre
				//in that.
				
				//val3 = address on the instruction space
				
				Worker *worker = Worker::init();
				Fibre *fib = Fibre::init();
				fib->RPC = val3;
				Worker::addFibre(worker, fib);
				Factory::spawnWorker(state->factory, worker);
				
				break;
			}
			
			case OPCODES::sendmsg: {
				break;
			}
			
			case OPCODES::readmsg: {
				break;
			}
			
			case OPCODES::eq: {
				
				if ( fibre->registers[RegisterID::R1].u64 == fibre->registers[RegisterID::R2].u64 ) {
					fibre->flag = 1;
				} else {
					fibre->flag = 0;
				}
				
				break;
	
			}
			
			case OPCODES::ilteq: {
				
				if ( std::bit_cast<int64_t>(fibre->registers[RegisterID::R1].u64) <= std::bit_cast<int64_t>(fibre->registers[RegisterID::R1].u64) ) {
					fibre->flag = 1;
				} else {
					fibre->flag = 0;
				}
				
				break;
				
			}
			
			case OPCODES::ulteq: {
				
				if ( fibre->registers[RegisterID::R1].u64 <= fibre->registers[RegisterID::R2].u64 ) {
					fibre->flag = 1;
				} else {
					fibre->flag = 0;
				}
				
				break;
				
			}
			
			case OPCODES::flteq: {
				
				float left = std::bit_cast<float>(static_cast<int32_t>(std::bit_cast<int64_t>(fibre->registers[RegisterID::R1].u64)));
				float right =  std::bit_cast<float>(static_cast<int32_t>(std::bit_cast<int64_t>(fibre->registers[RegisterID::R2].u64)));;
				
				if ( left <= right ) {
					fibre->flag = 1;
				} else {
					fibre->flag = 0;
				}
				
				break;
				
			}
			
			case OPCODES::dlteq: {
				
				double left = std::bit_cast<double>( fibre->registers[RegisterID::R1].u64 );
				double right = std::bit_cast<double>( fibre->registers[RegisterID::R2].u64 );;
				
				if ( left <= right ) {
					fibre->flag = 1;
				} else {
					fibre->flag = 0;
				}
				
				break;
				
			}
			
			case OPCODES::ilt: {
				
				if ( std::bit_cast<int64_t>(fibre->registers[RegisterID::R1].u64) < std::bit_cast<int64_t>(fibre->registers[RegisterID::R1].u64) ) {
					fibre->flag = 1;
				} else {
					fibre->flag = 0;
				}
				
				break;
				
			}
			
			case OPCODES::ult: {
				
				if ( fibre->registers[RegisterID::R1].u64 < fibre->registers[RegisterID::R2].u64 ) {
					fibre->flag = 1;
				} else {
					fibre->flag = 0;
				}
				
				break;
				
			}
			
			case OPCODES::flt: {
				
				float left = std::bit_cast<float>(static_cast<int32_t>(std::bit_cast<int64_t>(fibre->registers[RegisterID::R1].u64)));
				float right =  std::bit_cast<float>(static_cast<int32_t>(std::bit_cast<int64_t>(fibre->registers[RegisterID::R2].u64)));;
				
				if ( left < right ) {
					fibre->flag = 1;
				} else {
					fibre->flag = 0;
				}
				
				break;
				
			}
			
			case OPCODES::dlt: {
				
				double left = std::bit_cast<double>( fibre->registers[RegisterID::R1].u64 );
				double right = std::bit_cast<double>( fibre->registers[RegisterID::R2].u64 );;
				
				if ( left < right ) {
					fibre->flag = 1;
				} else {
					fibre->flag = 0;
				}
				
				break;
				
			}
			
			case OPCODES::band: {
				fibre->registers[RegisterID::ROUT].u64=
					fibre->registers[RegisterID::R1].u64 &
					fibre->registers[RegisterID::R2].u64;
				break;
			}
			
			case OPCODES::bor: {
				fibre->registers[RegisterID::ROUT].u64=
					fibre->registers[RegisterID::R1].u64 |
					fibre->registers[RegisterID::R2].u64;
				break;
			}
			
			case OPCODES::bxor: {
				fibre->registers[RegisterID::ROUT].u64=
					fibre->registers[RegisterID::R1].u64 ^
					fibre->registers[RegisterID::R2].u64;
				break;
			}
			
			case OPCODES::bnot: {
				fibre->registers[RegisterID::ROUT].u64=
					~fibre->registers[RegisterID::R1].u64;
				break;
			}
			
			case OPCODES::shl: {
				fibre->registers[RegisterID::ROUT].u64=
					fibre->registers[RegisterID::R1].u64 << val1;
				break;
			}
			
			case OPCODES::shr: {
				fibre->registers[RegisterID::ROUT].u64=
					fibre->registers[RegisterID::R1].u64 >> val1;
				break;
			}
			
			case OPCODES::mov: {
				fibre->registers[val1].u64 = fibre->registers[val2].u64;
				break;
			}
			
			case OPCODES::cls: {
				fibre->registers[val1].u64 = 0;
				break;
			}
			
			case OPCODES::movflag: {
				fibre->registers[val1].u64 = static_cast<uint64_t>( fibre->flag );
				break;
			}
			
			case OPCODES::hcpy: {
				//TODO
				break;
			}
			
			case OPCODES::fhcpy: {
				//TODO
				break;
			}
			
			case OPCODES::ccpy: {
				//TODO
				break;
			}
			
			case OPCODES::fccpy: {
				//TODO
				break;
			}
			
			case OPCODES::rtalloc: {
				break;
			}
			
			case OPCODES::rtfree: {
				break;
			}
			
			case OPCODES::ialloc: {
				break;
			}
			
			case OPCODES::falloc: {
				break;
			}
			
			case OPCODES::store: {
				break;
			}
			
			case OPCODES::fstore: {
				break;
			}
			
			case OPCODES::load: {
				break;
			}
			
			case OPCODES::fload: {
				break;
			}
			
			case OPCODES::inspect: {
				
				dump(fibre);
				break;
			}
			
			case OPCODES::exitf: {
				//exits the fibre
				if ( current->next == current && current->prev == current ) {
					//yeah we are at the same node basically.
					current->next = nullptr;
					current->prev = nullptr;
					Fibre::drop(current->node);
					CDLLWrapper<Fibre>::drop(current);
					return nullptr;
				}
				
				//else
				//rewire the next and previous terms basically.
				current->prev->next = current->next;
				current->next->prev = current->prev;
				
				CDLLWrapper<Fibre> *flush = current;
				current = current->next;
				fibre = current->node;
	
				flush->next = nullptr;
				flush->prev = nullptr;
				Fibre::drop(flush->node);
				CDLLWrapper<Fibre>::drop(flush);
				
				break;
			}	
		}
		
	}
	
}