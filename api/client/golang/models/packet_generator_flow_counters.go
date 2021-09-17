// Code generated by go-swagger; DO NOT EDIT.

package models

// This file was generated by the swagger tool.
// Editing this file might prove futile when you re-run the swagger generate command

import (
	"context"

	"github.com/go-openapi/errors"
	"github.com/go-openapi/strfmt"
	"github.com/go-openapi/swag"
	"github.com/go-openapi/validate"
)

// PacketGeneratorFlowCounters Packet generator flow statistics
//
// swagger:model PacketGeneratorFlowCounters
type PacketGeneratorFlowCounters struct {

	// The number of packets not transmitted due to errors
	// Required: true
	// Minimum: 0
	Errors *int64 `json:"errors"`

	// The total number of octets that have been transmitted
	// Required: true
	// Minimum: 0
	OctetsActual *int64 `json:"octets_actual"`

	// The total number of octets that were dropped due to overrunning the
	// transmit queue. Transmit packet drops are not enabled by default and
	// must be explicitly enabled.
	//
	// Minimum: 0
	OctetsDropped *int64 `json:"octets_dropped,omitempty"`

	// The total number of octets that should have been transmitted
	// Required: true
	// Minimum: 0
	OctetsIntended *int64 `json:"octets_intended"`

	// The total number of packets that have been transmitted
	// Required: true
	// Minimum: 0
	PacketsActual *int64 `json:"packets_actual"`

	// The total number of packets that were dropped due to overrunning the
	// transmit queue. Transmit packet drops are not enabled by default and
	// must be explicitly enabled.
	//
	// Minimum: 0
	PacketsDropped *int64 `json:"packets_dropped,omitempty"`

	// The total number of packets that should have been transmitted
	// Required: true
	// Minimum: 0
	PacketsIntended *int64 `json:"packets_intended"`

	// The timestamp of the first transmitted packet
	// Format: date-time
	TimestampFirst strfmt.DateTime `json:"timestamp_first,omitempty"`

	// The timestamp of the most recently transmitted packet
	// Format: date-time
	TimestampLast strfmt.DateTime `json:"timestamp_last,omitempty"`
}

// Validate validates this packet generator flow counters
func (m *PacketGeneratorFlowCounters) Validate(formats strfmt.Registry) error {
	var res []error

	if err := m.validateErrors(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validateOctetsActual(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validateOctetsDropped(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validateOctetsIntended(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validatePacketsActual(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validatePacketsDropped(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validatePacketsIntended(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validateTimestampFirst(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validateTimestampLast(formats); err != nil {
		res = append(res, err)
	}

	if len(res) > 0 {
		return errors.CompositeValidationError(res...)
	}
	return nil
}

func (m *PacketGeneratorFlowCounters) validateErrors(formats strfmt.Registry) error {

	if err := validate.Required("errors", "body", m.Errors); err != nil {
		return err
	}

	if err := validate.MinimumInt("errors", "body", *m.Errors, 0, false); err != nil {
		return err
	}

	return nil
}

func (m *PacketGeneratorFlowCounters) validateOctetsActual(formats strfmt.Registry) error {

	if err := validate.Required("octets_actual", "body", m.OctetsActual); err != nil {
		return err
	}

	if err := validate.MinimumInt("octets_actual", "body", *m.OctetsActual, 0, false); err != nil {
		return err
	}

	return nil
}

func (m *PacketGeneratorFlowCounters) validateOctetsDropped(formats strfmt.Registry) error {
	if swag.IsZero(m.OctetsDropped) { // not required
		return nil
	}

	if err := validate.MinimumInt("octets_dropped", "body", *m.OctetsDropped, 0, false); err != nil {
		return err
	}

	return nil
}

func (m *PacketGeneratorFlowCounters) validateOctetsIntended(formats strfmt.Registry) error {

	if err := validate.Required("octets_intended", "body", m.OctetsIntended); err != nil {
		return err
	}

	if err := validate.MinimumInt("octets_intended", "body", *m.OctetsIntended, 0, false); err != nil {
		return err
	}

	return nil
}

func (m *PacketGeneratorFlowCounters) validatePacketsActual(formats strfmt.Registry) error {

	if err := validate.Required("packets_actual", "body", m.PacketsActual); err != nil {
		return err
	}

	if err := validate.MinimumInt("packets_actual", "body", *m.PacketsActual, 0, false); err != nil {
		return err
	}

	return nil
}

func (m *PacketGeneratorFlowCounters) validatePacketsDropped(formats strfmt.Registry) error {
	if swag.IsZero(m.PacketsDropped) { // not required
		return nil
	}

	if err := validate.MinimumInt("packets_dropped", "body", *m.PacketsDropped, 0, false); err != nil {
		return err
	}

	return nil
}

func (m *PacketGeneratorFlowCounters) validatePacketsIntended(formats strfmt.Registry) error {

	if err := validate.Required("packets_intended", "body", m.PacketsIntended); err != nil {
		return err
	}

	if err := validate.MinimumInt("packets_intended", "body", *m.PacketsIntended, 0, false); err != nil {
		return err
	}

	return nil
}

func (m *PacketGeneratorFlowCounters) validateTimestampFirst(formats strfmt.Registry) error {
	if swag.IsZero(m.TimestampFirst) { // not required
		return nil
	}

	if err := validate.FormatOf("timestamp_first", "body", "date-time", m.TimestampFirst.String(), formats); err != nil {
		return err
	}

	return nil
}

func (m *PacketGeneratorFlowCounters) validateTimestampLast(formats strfmt.Registry) error {
	if swag.IsZero(m.TimestampLast) { // not required
		return nil
	}

	if err := validate.FormatOf("timestamp_last", "body", "date-time", m.TimestampLast.String(), formats); err != nil {
		return err
	}

	return nil
}

// ContextValidate validates this packet generator flow counters based on context it is used
func (m *PacketGeneratorFlowCounters) ContextValidate(ctx context.Context, formats strfmt.Registry) error {
	return nil
}

// MarshalBinary interface implementation
func (m *PacketGeneratorFlowCounters) MarshalBinary() ([]byte, error) {
	if m == nil {
		return nil, nil
	}
	return swag.WriteJSON(m)
}

// UnmarshalBinary interface implementation
func (m *PacketGeneratorFlowCounters) UnmarshalBinary(b []byte) error {
	var res PacketGeneratorFlowCounters
	if err := swag.ReadJSON(b, &res); err != nil {
		return err
	}
	*m = res
	return nil
}
