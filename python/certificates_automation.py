import logging
import argparse
import os.path
import re
import pathlib
import shutil
from datetime import datetime

DEFAULT_SOURCE_DIR = ".."
VALID_SUFFIXES = {".prv", ".cer"}
VALID_BYTE4_VALUES = {"12", "14"}
VALID_PROTOS = {"D40", "D30", "PC"}
VALID_FLAVORS = {"EU", "NA"}
MAC_FILE_REGEX_PATTERN = r"^([0-9A-Fa-f]{2}[_-]){5}([0-9A-Fa-f]{2}).*$"

logging.basicConfig(level=logging.DEBUG, format="%(asctime)s - %(levelname)s - %(message)s")
logger = logging.getLogger()
compiled_mac_file_regex = re.compile(MAC_FILE_REGEX_PATTERN)


def get_proto_flavor_prefix_for_path(proto: str, flavor: str = None) -> str:
    if proto and flavor:
        return f"{proto}_{flavor}_"
    return f"{proto}_"


def get_current_date() -> str:
    return datetime.now().strftime("%Y-%m-%d_%H-%M-%S")


def is_mac_file(path: str) -> bool:
    return bool(compiled_mac_file_regex.search(os.path.basename(path)))


def adjust_mac_file_name(file_name: str) -> str:
    new_file_stem = str(pathlib.Path(file_name).stem).replace('_', '-')
    return new_file_stem + str(pathlib.Path(file_name).suffix)


def validate_mac_file_suffix(file_path: str):
    file_suffix = str(pathlib.Path(file_path).suffix)
    assert file_suffix in VALID_SUFFIXES, f"Suffix '{file_suffix}' in '{file_path}' is not valid. " \
                                          f"It must be one of {VALID_SUFFIXES}"


def validate_mac_file_name(file_path: str):
    file_stem = str(pathlib.Path(file_path).stem)
    splitter = '-' if '-' in file_stem else '_'
    b1, b2, b3, b4, b5, b6 = file_stem.split(splitter)
    assert b4 in VALID_BYTE4_VALUES, f"Byte No.4 in filename of '{file_path}' is not valid. " \
                                     f"It must be one of {VALID_BYTE4_VALUES}"


def get_source_mac_files(source_dir: str, is_validate_suffix: bool) -> list:
    listed_dir = [os.path.join(source_dir, name) for name in os.listdir(source_dir)]
    mac_files_path = [path for path in listed_dir if is_mac_file(path)]
    if not mac_files_path:
        logger.warning("No mac files were found with the script requirements")
        exit()
    for file_path in mac_files_path:
        if is_validate_suffix:
            validate_mac_file_suffix(file_path)
        validate_mac_file_name(file_path)
    return mac_files_path


def create_output_dir(output_dir: str):
    if os.path.exists(output_dir):
        logger.warning(f"Output directory '{output_dir}' already exists")
        exit()
    try:
        os.mkdir(output_dir)
        logger.info(f"Created output directory '{output_dir}'")
    except OSError as error:
        logger.error(f"Could not create output directory. Reason: {error}")
        exit()


def copy_files(source_mac_files: list, output_dir: str, prefix: str, is_adjust_mac: bool):
    for source_mac_file in source_mac_files:
        new_file_name = os.path.basename(source_mac_file)
        if is_adjust_mac:
            new_file_name = adjust_mac_file_name(new_file_name)
        new_file_name = prefix + new_file_name
        destination_mac_file = os.path.join(output_dir, new_file_name)
        shutil.copyfile(source_mac_file, destination_mac_file)
        logger.info(f"Copied '{source_mac_file}' to '{destination_mac_file}'")


def validate_cli_args(cli_args: dict) -> dict:
    logger.debug("Validating cli args...")

    proto, flavor, source_dir = cli_args['proto'], cli_args['flavor'], cli_args['source_dir']
    if proto == "D40":
        assert not flavor, f"Proto {proto} MUST NOT be used with --flavor option"
    else:
        assert flavor, f"Proto {proto} MUST be used with --flavor option"

    assert os.path.exists(source_dir), f"The given source directory path '{source_dir}' does not exist"
    assert os.path.isdir(source_dir), f"The given source directory path '{source_dir}' is not a directory"


def adjust_cli_args(cli_args: dict):
    logger.debug("Adjusting cli args...")

    proto, flavor, output_dir = cli_args['proto'], cli_args['flavor'], cli_args['output_dir']
    if not output_dir:
        default_name = get_proto_flavor_prefix_for_path(proto, flavor) + get_current_date()
        cli_args['output_dir'] = os.path.join("..", default_name)


def get_cli_args() -> dict:
    parser = argparse.ArgumentParser()
    parser.add_argument("--proto", required=True, choices=VALID_PROTOS)
    parser.add_argument("--flavor", required=False, default=None, choices=VALID_FLAVORS)
    parser.add_argument("--adjust-mac", required=False, default=False, action=argparse.BooleanOptionalAction)
    parser.add_argument("--validate-suffix", required=False, default=False, action=argparse.BooleanOptionalAction)
    parser.add_argument("--output-dir", required=False, default=None)
    parser.add_argument("--source-dir", required=True, default=DEFAULT_SOURCE_DIR)
    cli_args = vars(parser.parse_args())

    validate_cli_args(cli_args)
    adjust_cli_args(cli_args)

    logger.info(f"CLI args after validation & adjustment:\n{cli_args}")
    return cli_args


def main():
    cli_args = get_cli_args()
    source_mac_files = get_source_mac_files(cli_args['source_dir'], cli_args['validate_suffix'])

    create_output_dir(cli_args['output_dir'])

    prefix = get_proto_flavor_prefix_for_path(cli_args['proto'], cli_args['flavor'])
    copy_files(source_mac_files, cli_args['output_dir'], prefix, cli_args['adjust_mac'])


if __name__ == "__main__":
    main()
