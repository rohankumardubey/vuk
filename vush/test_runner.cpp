#include "vush.hpp"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Catch2/catch.hpp"
#include <filesystem>
namespace fs = std::filesystem;

std::string stage_to_extension(stage_entry::type as) {
	switch (as) {
	case stage_entry::type::eVertex: return "vert";
	case stage_entry::type::eFragment: return "frag";
	default: assert(0); return "";
	}
}

void run_file(const std::string& src_file) {
	auto src = slurp(src_file);
	auto gen = parse_generate(src, src_file.c_str());
	size_t checks = 0;
	for (const auto& [aspect, pa] : gen.aspects) {
		for (auto& ps : pa.shaders) {
			auto control_file = src_file + "." + aspect + "." + stage_to_extension(ps.stage);
			if (fs::exists(fs::path(control_file))) {
				auto control = slurp(control_file);

				REQUIRE(ps.source == control);
				checks++;
			}
		}
	}
	REQUIRE(checks > 0);

}


TEST_CASE("basic", "[basic]") {
	add_rules(json::parse(slurp("../../vush/builtin_cfg.json")));

	run_file("../../tests/basic.vush");
}

TEST_CASE("ubos", "[ubos]") {
	add_rules(json::parse(slurp("../../vush/builtin_cfg.json")));

	run_file("../../tests/ubos.vush");
}